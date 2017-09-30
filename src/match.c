#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "match.h"

struct __match_t {
    bool     is_match;
    uint64_t match_len;
    char     *match_seq;
};
    
char
*match_n_chars(char *substr, int substr_len, char *str, int str_len)
{
    char c = *substr++;
    substr_len -= 1;
    str_len -= substr_len;
    while (--str_len >= 0)
    {
	if (*str++ == c && memcmp(substr, str, substr_len) == 0)
	{
	    return str-1;
	}
    }
    return NULL;
}

bool
match_char_ratio(char *substr, char *str, int substr_len, int mm_ratio)
{
    int score = 0, i;
    for (i=0; i<substr_len; ++i)
    {
	if (substr[i] == str[i])
	    score += 1;
	else
	    score -= mm_ratio;
    }
    return true ? score >= 0 : false;
}
