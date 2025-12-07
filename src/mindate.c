#include "mindate.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @file min_date.c
 * @brief Исходник отвечающий за сортировку от ранней к самой поздней дате.
 */

/**
 * @brief Объявление функции-компаратора.
 *
 * @return Возвращает 1, 0, -1 (в зависимости от знака).
 * @param first Входная структура строки сравнимого.
 * @param second Входная структура строки сравнителя.
 * @warning Не рекомендуется менять проверку для случая равенста!
 * @warning (Из-за логики работы qsort и условия ТЗ)
 */
int cmp_sents(const void *first, const void *second) {
    const size_t inf_f = ((const str_inform_t *)first)->inf;
    const size_t inf_s = ((const str_inform_t *)second)->inf;

    const size_t day_f = ((const str_inform_t *)first)->min_date->day;
    const size_t month_f = ((const str_inform_t *)first)->min_date->month;
    const size_t year_f = ((const str_inform_t *)first)->min_date->year;
    const size_t day_s = ((const str_inform_t *)second)->min_date->day;
    const size_t month_s = ((const str_inform_t *)second)->min_date->month;
    const size_t year_s = ((const str_inform_t *)second)->min_date->year;

    const size_t idx_f = ((const str_inform_t *)first)->index_str;
    const size_t idx_s = ((const str_inform_t *)second)->index_str;

    if (inf_f == 1 && inf_s != 1) {
        return 1;
    }
    if (inf_f != 1 && inf_s == 1) {
        return -1;
    }

    if (year_f != year_s) {
        return year_f - year_s;
    } else if (month_f != month_s) {
        return month_f - month_s;
    } else if (day_f != day_s) {
        return day_f - day_s;
    }

    if (idx_f > idx_s) { // случай, если даты равны
                         // (сохранение вхождения по индексам)
        return 1;
    } else {
        return -1;
    }
}

err_code find_min_date(strs_all *strs) {
    qsort(strs->str_inform, strs->total_len, sizeof(str_inform_t), cmp_sents);

    return SUCCESS;
}