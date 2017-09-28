#include <stdbool.h>
#ifndef _PCR_MATCH_H
struct __match_t;
typedef struct __match_t match_t;

// first place where substr of substr_len chars matches str of str_len chars
char *match_n_chars(char *substr, int substr_len, char *str, int str_len);

/* // TRUE if there are n matches per mismatch */
/* static bool match_char_ratio(char *substr, char *str, int str_len, int mm_ratio); */
#endif
