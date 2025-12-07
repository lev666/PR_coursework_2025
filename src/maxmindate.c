#include "maxmindate.h"

#include <stdio.h>

#include "readaform.h"

/**
 * @file maxmin_date.c
 * @brief Исходник отвечающий за нахождение поздней и ранней даты.
 */

err_code max_min_date(strs_all *strs) {
    for (size_t i = 0; i < strs->total_len; i++) {
        dateStrs *max_date = strs->str_inform[i].max_date;
        dateStrs *min_date = strs->str_inform[i].min_date;
        const size_t inf = strs->str_inform[i].inf;

        if (inf != TRUE) {
            fprintf(stdout, "Earliest date: %02d/%02d/%04d\n", min_date->day,
                    min_date->month, min_date->year);
            fprintf(stdout, "Latest date: %02d/%02d/%04d\n", max_date->day,
                    max_date->month, max_date->year);
        }
    }

    return SUCCESS;
}