#include "findcntdel.h"

#include <stdio.h>
#include <stdlib.h>

#define MEMFAIL "Error: Memory allocation error\n"

/**
 * @file findcntdel.c
 * @brief Исходник отвечающий за нахождение вхождения 19 века.
 */

int find_cnt_del(strs_all *strs) {
    size_t c_in_cent = 0;
    size_t shift_ptr = 0;

    for (size_t i = 0; i < strs->total_len; i++) {
        size_t temp_count_d = strs->str_a_len[i].date_c;
        for (size_t j = 0; j < temp_count_d; j++) {
            size_t temp_inf_d = strs->str_a_len[i].inf;
            if (temp_inf_d == 1) {
                break;
            } else {
                int temp_year_d = strs->str_a_len[i].curr_date_str[j].year;

                if (temp_year_d >= 1801 && temp_year_d < 1901) {
                    c_in_cent++;
                }
            }
        }
        if (c_in_cent == temp_count_d) {
            free(strs->str_a_len[i].curr_date_str);
            free(strs->str_a_len[i].minDate);
            free(strs->str_a_len[i].str);
        } else {
            if (shift_ptr != i) {
                strs->str_a_len[shift_ptr] =
                    strs->str_a_len[i]; // сдвигаем указатель со след на прошлый
            }
            shift_ptr++;
        }
    }

    strs->str_a_len =
        realloc_ptr(strs->str_a_len, sizeof(strsalen) * shift_ptr);

    strs->total_len = shift_ptr;

    return 0;
}