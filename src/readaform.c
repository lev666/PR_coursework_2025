#include "readaform.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define LENSTR_D 30 /**< длина строки по умолчанию */
#define HW_D 5      /**< Кол-во строк по умолчанию */
#define MEMFAIL "Error: Memory allocation error\n"

/**
 * @file readaform.c
 * @brief Исходник отвечающий за формирование строк в массив.
 */

/**
 * @brief Объявление функции проверки даты.
 *
 * @return Возвращает код состояния @see main()
 * @param day_c Текущий день (по итерации).
 * @param month_c Текущий месяц (по итерации).
 * @param year_c Текущий год (по итерации).
 */
int check_dates(int day_c, int month_c, int year_c);

/**
 * @brief Объявление функции увеличения кол-ва строк.
 *
 * @return Возвращает код состояния @see main()
 * @param strs Входная структура текста.
 * @param hw Максимальное кол-во строк.
 * @param curr_hw Текущая строка.
 * @param lenstr Длина строки.
 */
ErrCode incr_str_arr(strs_all *strs, size_t *hw, size_t curr_hw, size_t lenstr);

/**
 * @brief Объявление функции-компаратора.
 *
 * @return Возвращает 1, 0, -1 (в зависимости от знака).
 * @param ptr1 Входная структура строки сравнимого.
 * @param ptr2 Входная структура строки сравнителя.
 */
int cmp_dates(const dateStrs *ptr1, const dateStrs *ptr2);

/**
 * @brief Объявление функции парсинга дат.
 *
 * @return Возвращает код состояния @see main()
 * @param item Входная структура строки с информацией.
 */
ErrCode parse_dates(str_inform_t *item);

void *malloc_ptr(size_t size);

void *realloc_ptr(void *ptr, size_t size);

ErrCode read_a_format(strs_all *strs) {
    size_t hw = HW_D;
    size_t lenstr = LENSTR_D;

    strs->str_inform = malloc_ptr(sizeof(str_inform_t) * hw);

    for (size_t k = 0; k < hw; k++) {
        strs->str_inform[k].str = malloc_ptr(sizeof(char) * lenstr);
    }

    char c;
    size_t curr_hw = 0;
    size_t curr_lenstr = 0;
    size_t check_end = FALSE;
    size_t check_char = FALSE;

    while (((c = fgetc(stdin)) != EOF) && (check_end != 2)) {
        if (c == '\n') {
            if (check_end != TRUE) {
                check_end = FALSE;
            }
            check_end++;
            continue;
        }

        if (curr_hw == hw) {
            size_t incr_str_arr_r = incr_str_arr(strs, &hw, curr_hw, lenstr);
            if (incr_str_arr_r != SUCCESS)
                return incr_str_arr_r;
        }

        char *str_prs = strs->str_inform[curr_hw].str;
        str_inform_t *stralen_p = strs->str_inform;

        if (curr_lenstr + 1 == lenstr) { // прибавление 1 с учётом конца
            lenstr *= 2;
            str_prs = realloc_ptr(str_prs, sizeof(char) * lenstr);
            strs->str_inform[curr_hw].str = str_prs;
        }

        if (c != '.') {
            if (!isalnum(c) && c != '-' && check_char == FALSE) {
                continue;
            } else {
                check_char = TRUE;
            }
            str_prs[curr_lenstr++] = c;
        } else {
            char next_point_symbol = fgetc(stdin);
            str_prs[curr_lenstr++] = c;

            if (next_point_symbol == '.') {
                str_prs[curr_lenstr++] = next_point_symbol;
                while ((next_point_symbol = fgetc(stdin)) ==
                       '.') { // проверка на троеточия
                    str_prs[curr_lenstr++] = next_point_symbol;
                    if (curr_lenstr + 2 ==
                        lenstr) { // прибавление 2 с учётом конца + возврат
                        lenstr *= 2;
                        str_prs = realloc_ptr(str_prs, sizeof(char) * lenstr);
                        strs->str_inform[curr_hw].str = str_prs;
                    }
                }
                ungetc(next_point_symbol, stdin);
                continue;
            }

            str_prs[curr_lenstr] = '\0';
            stralen_p[curr_hw].lenstr = lenstr;
            check_char = FALSE;
            size_t duplc = FALSE;
            for (size_t k = 0; k < curr_hw; k++) {
                if (lenstr != stralen_p[k].lenstr)
                    continue;

                if (strcasecmp(str_prs, stralen_p[k].str) == 0) {
                    duplc = TRUE;
                    free(str_prs);
                    stralen_p[curr_hw].lenstr = 0;
                    str_prs = malloc_ptr(sizeof(char) * LENSTR_D);
                    strs->str_inform[curr_hw].str = str_prs;
                    break;
                }
            }

            if (duplc != TRUE) {
                size_t *idx_str = &(stralen_p[curr_hw].index_str);
                *idx_str = curr_hw;

                size_t parse_dates_r = parse_dates(&stralen_p[curr_hw]);
                if (parse_dates_r != SUCCESS)
                    return parse_dates_r;

                curr_hw++;
            }
            lenstr = LENSTR_D;
            curr_lenstr = 0;
        }
    }

    if (curr_hw < hw) {
        for (size_t j = curr_hw; j < hw; j++) {
            free(strs->str_inform[j].str);
        }
        strs->str_inform =
            realloc_ptr(strs->str_inform, sizeof(str_inform_t) * curr_hw);
    }
    size_t *totallen = &(strs->total_len);
    *totallen = curr_hw;

    return SUCCESS;
}

int check_dates(const int day_c, const int month_c, const int year_c) {
    if (day_c > 0 && month_c > 0 && year_c > 0) {
        if (month_c > 12 || day_c > 31)
            return TRUE;

        if (day_c <= 31) {
            size_t check_day = 0;
            int leap = ((year_c % 4 == 0 && year_c % 100 != 0) ||
                        (year_c % 400) == 0); // проверка на вис год

            switch (month_c) {
            case 4:
            case 6:
            case 9:
            case 11:
                check_day = day_c > 30 ? TRUE : FALSE;
                break;
            case 2:
                int check_leap = leap ? 29 : 28;
                check_day = day_c > check_leap ? TRUE : FALSE;
                break;
            default:
                check_day = day_c > 31 ? TRUE : FALSE;
            }

            if (check_day)
                return TRUE;
        } else
            return TRUE;
    } else {
        return TRUE;
    }

    return FALSE;
}

void *malloc_ptr(size_t size) {
    void *temp_ptr = (void *)malloc(size);
    if (temp_ptr == NULL) {
        fprintf(stdout, MEMFAIL);
        exit(EXIT_FAILURE);
    }
    return temp_ptr;
}

void *realloc_ptr(void *ptr, size_t size) {
    void *temp_ptr = (void *)realloc(ptr, size);
    if (temp_ptr == NULL) {
        fprintf(stdout, MEMFAIL);
        exit(EXIT_FAILURE);
    }
    return temp_ptr;
}

ErrCode incr_str_arr(strs_all *strs, size_t *hw, size_t curr_hw,
                     size_t lenstr) {
    *hw *= 2;
    strs->str_inform =
        realloc_ptr(strs->str_inform, sizeof(str_inform_t) * (*hw));
    strs->total_len = (*hw);

    for (size_t j = curr_hw; j < (*hw); j++) {
        strs->str_inform[j].str = malloc_ptr(sizeof(char) * lenstr);
    }

    return SUCCESS;
}

int cmp_dates(const dateStrs *ptr1, const dateStrs *ptr2) {
    if (ptr1->year != ptr2->year) {
        return ptr1->year - ptr2->year;
    } else if (ptr1->month != ptr2->month) {
        return ptr1->month - ptr2->month;
    } else if (ptr1->day != ptr2->day) {
        return ptr1->day - ptr2->day;
    }

    return 0;
}

ErrCode parse_dates(str_inform_t *item) {
    char *curr_str = item->str;
    int dayCurr_str, monthCurr_str, yearCurr_str;
    size_t temp_ptr = 0;

    size_t capacity_dates = 5;

    item->dates_str = NULL;
    item->minDate = NULL;
    item->maxDate = NULL;

    item->dates_str = malloc_ptr(sizeof(dateStrs) * capacity_dates);

    if (item->minDate == NULL) {
        item->minDate = malloc_ptr(sizeof(dateStrs));
        item->minDate->day = item->minDate->month = item->minDate->year = -1;
    }
    if (item->maxDate == NULL) {
        item->maxDate = malloc_ptr(sizeof(dateStrs));
        item->maxDate->day = item->maxDate->month = item->maxDate->year = -1;
    }

    size_t count_dates_str = 0;

    while (*curr_str != '\0') {
        if (sscanf(curr_str, "%d/%d/%d%ln", &dayCurr_str, &monthCurr_str,
                   &yearCurr_str, &temp_ptr) == 3) {
            curr_str += temp_ptr;

            if (check_dates(dayCurr_str, monthCurr_str, yearCurr_str)) {
                continue;
            }

            if (count_dates_str == capacity_dates) {
                capacity_dates *= 2;
                item->dates_str = realloc_ptr(
                    item->dates_str, sizeof(dateStrs) * capacity_dates);
            }

            item->dates_str[count_dates_str].day = dayCurr_str;
            item->dates_str[count_dates_str].month = monthCurr_str;
            item->dates_str[count_dates_str].year = yearCurr_str;

            if (cmp_dates(&(item->dates_str[count_dates_str]), item->maxDate) >
                0) {
                *item->maxDate = item->dates_str[count_dates_str];
            }
            if (item->minDate->day == -1 && item->minDate->month == -1 &&
                item->minDate->year == -1) {
                *item->minDate = item->dates_str[count_dates_str];
            } else if (cmp_dates(&(item->dates_str[count_dates_str]),
                                 item->minDate) < 0) {
                *item->minDate = item->dates_str[count_dates_str];
            }
            count_dates_str++;

            dayCurr_str = monthCurr_str = yearCurr_str = 0;
        } else {
            curr_str++;
        }
    }

    if (count_dates_str == 0) {
        item->inf = TRUE;
        item->date_c = 1; // inf
    } else {
        item->inf = FALSE;
        if (count_dates_str < capacity_dates) {
            item->dates_str = realloc_ptr(item->dates_str,
                                          sizeof(dateStrs) * count_dates_str);
        }
        item->date_c = count_dates_str;
    }

    return SUCCESS;
}