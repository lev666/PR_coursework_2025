#pragma once
#include <stdio.h>

typedef struct {
    size_t day;
    size_t month;
    size_t year;

    size_t inf;
} dateStrs;

typedef struct {
    char* str;
    size_t lenstr;

    dateStrs* curr_date_str;
    dateStrs* minDate;
    size_t date_c;

    size_t index_str;
} strsalen;

typedef struct {
    strsalen* str_a_len;
    size_t total_len;
} strs_all;

unsigned int read_a_format(strs_all* strs);