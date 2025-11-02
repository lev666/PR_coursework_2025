#pragma once
#include <stdio.h>

typedef struct {
    char* str;
    size_t lenstr;
} strsalen;

typedef struct {
    strsalen* str_a_len;
    size_t total_len;
} strs_all;


unsigned int read_a_format(strs_all* strs);