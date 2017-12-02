#include <argp.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "match.h"
#include "htslib/faidx.h"

static struct argp_option options[] = {
    {"verbose",      'v', 0,              0, "be verbose", 0},
    {"output",       'o', "OUTPUT",       0, "file to write to (default stdout)", 0},
    {"reference",    'r', "REFERENCE",    0,
     "reference genome file in fasta format, with accompanying *.fai index", 0},
    {"query-string", 'q', "QUERY_STRING", 0,
     "contig:start-stop string to query across. (Default is the whole fasta file)", 0},
    {0},
};

struct cli_arguments
{
    int verbose;
    char *output;
    char *reference;
    char *query_string;
};

static error_t
parse_args(int key, char *arg, struct argp_state *state)
{
    struct cli_arguments *args = state->input;

    switch(key)
    {
    case 'v':
	args->verbose = 1;
	break;
    case 'o':
	args->output = arg;
	break;
    case 'r':
	args->reference = arg;
	break;
    case 'q':
	args->query_string = arg;
	break;
    case ARGP_KEY_ARG:
	argp_error(state, "invalid option -- '%s'", arg);
	break;
    default:
	return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

const char *argp_program_version = PCR_VERSION;
const char *argp_program_bug_address = PCR_BUG_ADDRESS;
char doc[] = PCR_DOC_STRING;

static struct argp argp = {
    options,
    parse_args,
    "",     // args_doc
    doc,
    0,      // children
    0,      // help_filter
    0       // argp_domain
};

int
file_readable(char *fname)
{
    if(access(fname, R_OK) != -1)
	return 1;
    else
	return 0;
}

/* char * */
/* validate_query_string(char *query_string) */
/* { */
/*     if(strlen(query_string) == 0) */
/*     { */
/* 	puts("query string is empty"); */
/* 	exit(1); */
/*     } */
/*     return query_string; */
/* } */

int
main(int argc, char **argv)
{
    struct cli_arguments args;

    args.verbose = 0;
    args.output = "-";
    args.query_string = "";
    args.reference = "";

    argp_parse(&argp, argc, argv, 0, 0, &args);

    if(args.verbose)
    {
	printf("Parsed Arguments:\n"
	       "output = %s\n"
	       "reference = %s\n"
	       "verbose = %s\n",
	       args.output,
	       args.reference,
	       args.verbose ? "yes" : "no");
    }

    // TODO: make this work
    /* if(argc == 1) */
    /* { */
    /* 	argp_state_help(&argp, stdout, 0); */
    /* 	exit(1); */
    /* } */

    if(strlen(args.reference) == 0)
    {
	puts("No reference specified");
	exit(1);
    }

    if(strlen(args.query_string) == 0)
    {
	 puts("No query string specified");
	 exit(1);
    }

    if(!file_readable(args.reference))
    {
	printf("Reference is not readable: %s\n", args.reference);
	exit(1);
    }

    faidx_t *fai = fai_load(args.reference);
    if(!fai)
    {
	printf("Could not load reference %s\n", args.reference);
	exit(1);
    }

    int seq_len;
    char *seq = fai_fetch(fai, args.query_string, &seq_len);
    if(seq_len < 0)
    {
	printf("Failed to fetch sequence in %s\n", args.query_string);
	exit(1);
    }

    /* size_t i, seq_sz = seq_len; */
    /* for(i=0; i<seq_sz; i+=60) */
    /* { */
    /* 	size_t len = i + 60 < seq_sz ? 60 : seq_sz - i; */
    /* 	if(fwrite(seq + i, 1, len, stdout) < len || */
    /* 	   putchar('\n') == EOF) { */
    /* 	    puts("Failed to write output"); */
    /* 	    exit(1); */
    /* 	} */
    /* } */

    char *to_match = "TGGGCT";
    char *__chrom = "chr2";
    int __start = 19990 - 1;
    int __stop = 20040;
    int seq_length = 0;
    int NOMATCH = 0;
    int match_len = 4;
    for(int i=__start; i<__stop; i+=1)
    {
	if((seq = faidx_fetch_seq(fai, __chrom, i, i + 20, &seq_length)))
	{
	    for(int _i=0; _i<i-__start; _i+=1)
	    {
	    	putchar(' ');
	    }
	    if(!NOMATCH)
	    {
		char *m = match_n_chars(to_match, match_len, seq, strlen(seq));
		if(m)
		    printf("%s\n", m);
		else
		    putchar('\n');
	    } else {
		printf("%s\n", seq);
	    }


	    /* if(match_char_ratio(to_match, seq, strlen(to_match), 2)) */
	    /* 	puts(seq); */
	} else {
	    puts("No sequence found");
	    exit(1);
	}
    }

    free(seq);
    fai_destroy(fai);
    exit(0);
}
