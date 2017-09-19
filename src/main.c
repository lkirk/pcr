#include <argp.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "htslib/faidx.h"

const char *argp_program_version = PCR_VERSION;
const char *argp_program_bug_address = "<nope@nope.bla>";

static char doc[] = "this prog does stuff";

static char args_doc[] = "";

static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "be verbose"},
    {"output", 'o', "OUTPUT", 0, "file to write to (default stdout)"},
    {"reference", 'r', "REFERENCE", 0, "reference genome file in fasta "
                                       "format, with accompanying *.fai index"},
    {0},
};

struct cli_arguments
{
    int verbose;
    char *output_file;
    char *reference;
};

static error_t
parse_args(int key, char *arg, struct argp_state *state)
{
    struct cli_arguments *args = state->input;
    char unknown_pos_arg_msg[80];

    switch(key)
    {
    case 'v':
	args->verbose = 1;
	break;
    case 'o':
	args->output_file = arg;
	break;
    case 'r':
	args->reference = arg;
	break;
    case ARGP_KEY_ARG:
	sprintf(unknown_pos_arg_msg, "invalid option -- '%s'", arg);
	argp_error(state, unknown_pos_arg_msg);
	break;
    case ARGP_KEY_END:
	if(state->arg_num < 0)
	    argp_usage(state);
	break;

    default:
	return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_args, args_doc, doc};

int
main(int argc, char **argv)
{
    struct cli_arguments args;

    args.verbose = 0;
    args.output_file = "-";

    argp_parse(&argp, argc, argv, 0, 0, &args);

    if(args.verbose)
    {
	printf("Parsed Arguments:\n"
	       "output-file = %s\n"
	       "reference = %s\n"
	       "verbose = %s\n",
	       args.output_file,
	       args.reference,
	       args.verbose ? "yes" : "no");
    }

    if(strlen(args.reference) == 0)
    {
	puts("No reference specified");
	exit(1);
    }

    faidx_t *fai = fai_load(args.reference);
    if (!fai)
    {
	printf("Could not load fai index of %s\n"
	       "Create with `samtools fadix`", args.reference);
	exit(1);
    }

    int seq_len;
    char *seq = fai_fetch(fai, "chr2:20,000-30,000", &seq_len);
    if(seq_len < 0) {
	printf("Failed to fetch sequence in %s\n", "chr2:20,000-30,000");
	exit(1);
    }
    size_t i, seq_sz = seq_len;
    for(i=0; i<seq_sz; i+=60)
    {
	size_t len = i + 60 < seq_sz ? 60 : seq_sz - i;
	if(fwrite(seq + i, 1, len, stdout) < len ||
	   putchar('\n') == EOF) {
	    puts("Failed to write output");
	    exit(1);
	}
    }
    free(seq);
    fai_destroy(fai);
    exit(0);
}
