#include "findcntdel.h"

#include <stdio.h>
#include <stdlib.h>

#define MEMFAIL "Error: Memory allocation error\n"
#define DATE_F 1801
#define DATE_E 1901

/**
 * @file findcntdel.c
 * @brief Исходник отвечающий за нахождение вхождения 19 века.
 */

err_code find_cnt_del(strs_all *strs) {
    size_t c_in_cent = 0;
    size_t shift_ptr = 0;

    for (size_t i = 0; i < strs->total_len; i++) {
        size_t temp_count_d = strs->str_inform[i].date_c;
        for (size_t j = 0; j < temp_count_d; j++) {
            size_t temp_inf_d = strs->str_inform[i].inf;
            if (temp_inf_d == TRUE) {
                break;
            } else {
                int temp_year_d = strs->str_inform[i].dates_str[j].year;

                if (temp_year_d >= DATE_F && temp_year_d < DATE_E) {
                    c_in_cent++;
                }
            }
        }
        if (c_in_cent == temp_count_d) {
            free(strs->str_inform[i].dates_str);
            free(strs->str_inform[i].min_date);
            free(strs->str_inform[i].max_date);
            free(strs->str_inform[i].str);
        } else {
            if (shift_ptr != i) {
                strs->str_inform[shift_ptr] =
                    strs->str_inform[i]; // сдвигаем указатель со след на
                                         // прошлый
            }
            shift_ptr++;
        }
        c_in_cent = 0;
    }

    strs->str_inform =
        realloc_ptr(strs->str_inform, sizeof(str_inform_t) * shift_ptr);

    strs->total_len = shift_ptr;

    return SUCCESS;
}