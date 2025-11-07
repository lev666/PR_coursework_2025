#include "minDate.h"
#include "readaform.h"
#include <stdlib.h>

int cmp_sents(const void* ptr1, const void* ptr2) {
    const size_t inf_p1 = ((const strsalen* )ptr1)->inf;
    const size_t inf_p2 = ((const strsalen* )ptr2)->inf;

    const size_t day_p1 = ((const strsalen* )ptr1)->minDate->day;
    const size_t month_p1 = ((const strsalen* )ptr1)->minDate->month;
    const size_t year_p1 = ((const strsalen* )ptr1)->minDate->year;
    const size_t day_p2 = ((const strsalen* )ptr2)->minDate->day;
    const size_t month_p2 = ((const strsalen* )ptr2)->minDate->month;
    const size_t year_p2 = ((const strsalen* )ptr2)->minDate->year;

    const size_t idx_p1 = ((const strsalen* )ptr1)->index_str;
    const size_t idx_p2 = ((const strsalen* )ptr2)->index_str;

    if (inf_p1 == 1 && inf_p2 != 1) {
        return 1;
    }
    if (inf_p1 != 1 && inf_p2 == 1) {
        return -1;
    }

    if (year_p1 != year_p2) {
        return year_p1 - year_p2;
    } else if (month_p1 != month_p2) {
        return month_p1 - month_p2;
    } else if (day_p1 != day_p2) {
        return day_p1 - day_p2;
    }

    if (idx_p1 > idx_p2) { // случай, если даты равны (сохранение вхождения)
        return 1;
    } else {
        return -1;
    }
}

unsigned int findMinDate(strs_all* strs) {
    qsort(strs->str_a_len, strs->total_len, sizeof(strsalen), cmp_sents);

    return 0;
}