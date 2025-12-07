#include "currdate.h"

#include <stdio.h>
#include <time.h>

#define LEN_DATE_STR 11

/**
 * @file currdate.c
 * @brief Исходник отвечающий за нахождение предложенией с вхождением текущей
 * даты.
 */

err_code curr_date(strs_all *strs) {
    time_t times = time(0);
    struct tm *curr_time = localtime(&times);

    char form_curr_time[LEN_DATE_STR];
    strftime(form_curr_time, LEN_DATE_STR, "%d/%m/%Y", curr_time);
    int data, month, year = -1;
    if (sscanf(form_curr_time, "%d/%d/%d", &data, &month, &year) != 3) {
        fprintf(stdout, "Error: string format error\n");
        return SUCCESS;
    }

    for (size_t i = 0; i < strs->total_len; i++) {
        size_t temp_count_d = strs->str_inform[i].date_c;
        for (size_t j = 0; j < temp_count_d; j++) {
            size_t temp_inf_d = strs->str_inform[i].inf;
            if (temp_inf_d == 1) {
                break;
            } else {
                int temp_month_d = strs->str_inform[i].dates_str[j].month;
                int temp_year_d = strs->str_inform[i].dates_str[j].year;

                if (temp_month_d == month && temp_year_d == year) {
                    char *curr_sen = strs->str_inform[i].str;
                    printf("%s\n", curr_sen);
                }
            }
        }
    }

    return SUCCESS;
}