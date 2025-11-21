#include "minDate.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @file minDate.c
 * @brief Исходник отвечающий за сортировку от ранней к самой поздней дате.
 */

/**
 * @brief Объявление функции-компаратора.
 *
 * @return Возвращает 1, 0, -1 (в зависимости от знака).
 * @param ptr1 Входная структура строки сравнимого.
 * @param ptr2 Входная структура строки сравнителя.
 * @warning Не рекомендуется менять проверку для случая равенста!
 * @warning (Из-за логики работы qsort и условия ТЗ)
 */
int cmp_sents(const void *ptr1, const void *ptr2) {
    const size_t inf_p1 = ((const str_inform_t *)ptr1)->inf;
    const size_t inf_p2 = ((const str_inform_t *)ptr2)->inf;

    const size_t day_p1 = ((const str_inform_t *)ptr1)->minDate->day;
    const size_t month_p1 = ((const str_inform_t *)ptr1)->minDate->month;
    const size_t year_p1 = ((const str_inform_t *)ptr1)->minDate->year;
    const size_t day_p2 = ((const str_inform_t *)ptr2)->minDate->day;
    const size_t month_p2 = ((const str_inform_t *)ptr2)->minDate->month;
    const size_t year_p2 = ((const str_inform_t *)ptr2)->minDate->year;

    const size_t idx_p1 = ((const str_inform_t *)ptr1)->index_str;
    const size_t idx_p2 = ((const str_inform_t *)ptr2)->index_str;

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

    if (idx_p1 > idx_p2) { // случай, если даты равны
                           // (сохранение вхождения по индексам)
        return 1;
    } else {
        return -1;
    }
}

ErrCode findMinDate(strs_all *strs) {
    qsort(strs->str_inform, strs->total_len, sizeof(str_inform_t), cmp_sents);

    return SUCCESS;
}