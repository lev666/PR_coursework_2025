#include "maxmindate.h"

#include <stdio.h>

#include "readaform.h"

/**
 * @file maxmindate.c
 * @brief Исходник отвечающий за нахождение поздней и ранней даты.
 */

int max_min_date(strs_all *strs) {
    for (size_t i = 0; i < strs->total_len; i++) {
        dateStrs *maxDate = strs->str_a_len[i].maxDate;
        dateStrs *minDate = strs->str_a_len[i].minDate;
        const size_t inf = strs->str_a_len[i].inf;

        if (inf != 1) {
            fprintf(stdout, "Earliest date: %02d/%02d/%04d\n", minDate->day,
                    minDate->month, minDate->year);
            fprintf(stdout, "Latest date: %02d/%02d/%04d\n", maxDate->day,
                    maxDate->month, maxDate->year);
        }
    }

    return 0;
}