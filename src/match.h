#pragma once

#include <stdbool.h>
#include <stdint.h>

struct __match_t;
typedef struct __match_t match_t;

// first place where substr of substr_len chars matches str of str_len chars
uint8_t *match_n_chars(uint8_t *substr, int substr_len, uint8_t *str, int str_len);

// TRUE if there are n matches per mismatch
bool match_char_ratio(uint8_t *substr, uint8_t *str, int substr_len, int mm_ratio);
