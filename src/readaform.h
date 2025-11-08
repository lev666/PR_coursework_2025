#pragma once

typedef struct {
    int day;
    int month;
    int year;
} dateStrs;

typedef struct {
    char* str;
    size_t lenstr;

    dateStrs* curr_date_str;
    dateStrs* minDate;
    size_t inf;
    size_t date_c;

    size_t index_str;
} strsalen;

typedef struct {
    strsalen* str_a_len;
    size_t total_len;
} strs_all;

unsigned int read_a_format(strs_all* strs);