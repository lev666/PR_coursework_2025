#include <stdio.h>
#include "currdate.h"

unsigned int curr_date(strs_all* strs) {
    time_t times = time(0);
    struct tm* curr_time = localtime(&times);

    char form_curr_time[11];
    strftime(form_curr_time, 11, "%d/%m/%Y", curr_time);
    unsigned int data, month, year = 0;
    if (sscanf(form_curr_time, "%d/%d/%d", &data, &month, &year) != 3) {
        fprintf(stdout, "Error: string formatt error\n");
        return 1;
    }

    for (size_t i = 0; i < strs->total_len; i++) {
        size_t temp_count_d = strs->str_a_len[i].date_c;
        for (size_t j = 0; j < temp_count_d; j++) {
            size_t temp_inf_d = strs->str_a_len[i].curr_date_str[j].inf;
            if (temp_inf_d == 1) {
                break;
            } else {
                size_t temp_month_d = strs->str_a_len[i].curr_date_str[j].month;
                size_t temp_year_d = strs->str_a_len[i].curr_date_str[j].year;

                if (temp_month_d == month && temp_year_d == year) {
                    char* curr_sen = strs->str_a_len[i].str;
                    printf("%s\n", curr_sen);
                }
            }
        }
    }

    return 0;
}