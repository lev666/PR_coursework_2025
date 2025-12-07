#include "readaform.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define LENSTR_D 30 /**< длина строки по умолчанию */
#define HW_D 5      /**< Кол-во строк по умолчанию */
#define DATES_D 5   /**< Кол-во дат по умолчанию */
#define MEMFAIL "Error: Memory allocation error\n"
/**< Ошибка об выделении памяти */
#define ALL_MONTHS 12   /**< Количество месяцев */
#define DEF_ALL_DAYS 31 /**< Количество дней */
#define DAYS_NOVEM 30   /**< Дней в ноябре */
#define FEB_LEAP_T 29   /**< Дней в високосном феврале */
#define FEB_LEAP_F 28   /**< Дней в обычном феврале */
#define BREAK_DATE -1   /**< Затычка даты */
#define POINT '.'       /**< Точка */
#define LINE_BREAK '\0' /**< Конец строки (нуль-терминатор) */

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
err_code incr_str_arr(strs_all *strs, size_t *hw, size_t curr_hw,
                      size_t lenstr);

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
err_code parse_dates(str_inform_t *item);

/**
 * @brief Объявление функции аллокации.
 *
 * @return Возвращает адрес памяти.
 * @param size кол-во байтов.
 */
void *malloc_ptr(size_t size);

/**
 * @brief Объявление функции реаллокации.
 *
 * @return Возвращает адрес памяти.
 * @param ptr указатель на исходный указатель памяти.
 * @param size кол-во байтов.
 */
void *realloc_ptr(void *ptr, size_t size);

/**
 * @brief Инициализация хранилища строк.
 *
 * @param strs Входная структура текста.
 * @param hw Максимальное кол-во строк.
 * @param lenstr Длина строки.
 */
void init_strs_mem(strs_all *strs, size_t hw, size_t lenstr);

/**
 * @brief Расширение буфера строки.
 *
 * @param strs Входная структура текста.
 * @param curr_hw Текущая строка.
 * @param lenstr Длина строки.
 * @param curr_lenstr Текущая длина строки.
 * @param str_prs Заменяемая строка.
 */
void expand_str_buffer(char **str_prs, size_t curr_lenstr, size_t *lenstr,
                       strs_all *strs, size_t curr_hw);

/**
 * @brief Обработка троеточий в строке.
 *
 * @param strs Входная структура текста.
 * @param curr_hw Текущая строка.
 * @param lenstr Длина строки.
 * @param curr_lenstr Текущая длина строки.
 * @param str_prs Заменяемая строка.
 * @param с Символ обработки.
 * @return Возвращает код состояния @see main()
 */
int find_ellipsis(char **str_prs, size_t *curr_lenstr, size_t *lenstr,
                  strs_all *strs, size_t curr_hw, char c);

/**
 * @brief Обработка дубликатов в тексте.
 *
 * @param strs Входная структура текста.
 * @param curr_hw Текущая строка.
 * @param lenstr Длина строки.
 * @param str_prs Заменяемая строка.
 * @return Возвращает код состояния @see main()
 */
int check_and_reset_duplicate(strs_all *strs, size_t curr_hw, char **str_prs,
                              size_t lenstr);

/**
 * @brief Сужение итогой памяти.
 *
 * @param strs Входная структура текста.
 * @param curr_hw Текущая строка.
 * @param hw Максимальное кол-во строк.
 */
void resize_mem(strs_all *strs, size_t curr_hw, size_t hw);

/**
 * @brief Обновление max/min дат.
 *
 * @param item Входная структура строки с информацией.
 * @param new_date новая дата.
 */
void update_dates(str_inform_t *item, dateStrs new_date);

/**
 * @brief Инициализация хранилища дат.
 *
 * @param item Входная структура строки с информацией.
 * @param new_date новая дата.
 */
void init_date_storage(str_inform_t *item, size_t capacity);

/**
 * @brief Запись даты.
 *
 * @param item Входная структура строки с информацией.
 * @param date текущая дата.
 * @param count кол-во дат.
 * @param capacity запас хранилища дат.
 */
void add_date(str_inform_t *item, dateStrs date, size_t *count,
              size_t *capacity);

err_code read_a_format(strs_all *strs) {
    size_t hw = HW_D;
    size_t lenstr = LENSTR_D;

    init_strs_mem(strs, hw, lenstr);

    char c;
    size_t curr_hw = 0;
    size_t curr_lenstr = 0;
    size_t check_end = FALSE;
    size_t check_char = FALSE;

    while (((c = fgetc(stdin)) != EOF) && (check_end != 2)) {
        if (c == '\n') {
            check_end++;
            continue;
        }
        check_end = 0;

        if (curr_hw == hw) {
            size_t incr_str_arr_r = incr_str_arr(strs, &hw, curr_hw, lenstr);
            if (incr_str_arr_r != SUCCESS)
                return incr_str_arr_r;
        }

        char *str_prs = strs->str_inform[curr_hw].str;
        str_inform_t *stralen_p = strs->str_inform;

        expand_str_buffer(&str_prs, curr_lenstr, &lenstr, strs, curr_hw);

        if (c != POINT) {
            if (!isalnum(c) && c != '-' && check_char == FALSE) {
                continue;
            } else {
                check_char = TRUE;
            }
            str_prs[curr_lenstr++] = c;
        } else {
            char next_peek = fgetc(stdin);
            ungetc(next_peek, stdin);

            if (next_peek == POINT) {
                find_ellipsis(&str_prs, &curr_lenstr, &lenstr, strs, curr_hw,
                              c);
                continue;
            }
            str_prs[curr_lenstr++] = c;
            str_prs[curr_lenstr] = LINE_BREAK;
            stralen_p[curr_hw].lenstr = lenstr;
            check_char = FALSE;

            size_t duplc =
                check_and_reset_duplicate(strs, curr_hw, &str_prs, lenstr);

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

    resize_mem(strs, curr_hw, hw);

    return SUCCESS;
}

void init_strs_mem(strs_all *strs, size_t hw, size_t lenstr) {
    strs->str_inform = malloc_ptr(sizeof(str_inform_t) * hw);
    for (size_t k = 0; k < hw; k++) {
        strs->str_inform[k].str = malloc_ptr(sizeof(char) * lenstr);
    }
}

void expand_str_buffer(char **str_prs, size_t curr_lenstr, size_t *lenstr,
                       strs_all *strs, size_t curr_hw) {
    if (curr_lenstr + 1 == *lenstr) { // 1 - обработка перевода строки
        *lenstr *= 2;                 // увеличение размера в 2 раза
        *str_prs = realloc_ptr(*str_prs, sizeof(char) * (*lenstr));
        strs->str_inform[curr_hw].str = *str_prs;
    }
}

int find_ellipsis(char **str_prs, size_t *curr_lenstr, size_t *lenstr,
                  strs_all *strs, size_t curr_hw, char c) {
    char next_point_symbol = fgetc(stdin);
    (*str_prs)[(*curr_lenstr)++] = c;

    if (next_point_symbol == POINT) {
        (*str_prs)[(*curr_lenstr)++] = next_point_symbol;

        while ((next_point_symbol = fgetc(stdin)) == POINT) {
            (*str_prs)[(*curr_lenstr)++] = next_point_symbol;

            if (*curr_lenstr + 2 == *lenstr) {
                *lenstr *= 2; // увеличение размера в 2 раза
                *str_prs = realloc_ptr(*str_prs, sizeof(char) * (*lenstr));
                strs->str_inform[curr_hw].str = *str_prs;
            }
        }
        ungetc(next_point_symbol, stdin);
        return TRUE;
    }

    ungetc(next_point_symbol, stdin);
    return FALSE;
}

int check_and_reset_duplicate(strs_all *strs, size_t curr_hw, char **str_prs,
                              size_t lenstr) {
    str_inform_t *stralen_p = strs->str_inform;
    size_t duplc = FALSE;

    for (size_t k = 0; k < curr_hw; k++) {
        if (lenstr != stralen_p[k].lenstr)
            continue;

        if (strcasecmp(*str_prs, stralen_p[k].str) == 0) {
            duplc = TRUE;
            free(*str_prs);
            stralen_p[curr_hw].lenstr = 0;
            *str_prs = malloc_ptr(sizeof(char) * LENSTR_D);
            strs->str_inform[curr_hw].str = *str_prs;
            break;
        }
    }
    return duplc;
}

void resize_mem(strs_all *strs, size_t curr_hw, size_t hw) {
    if (curr_hw < hw) {
        for (size_t j = curr_hw; j < hw; j++) {
            free(strs->str_inform[j].str);
        }
        strs->str_inform =
            realloc_ptr(strs->str_inform, sizeof(str_inform_t) * curr_hw);
    }
    strs->total_len = curr_hw;
}

int check_dates(const int day_c, const int month_c, const int year_c) {
    if (day_c > 0 && month_c > 0 && year_c > 0) {
        if (month_c > ALL_MONTHS || day_c > DEF_ALL_DAYS)
            return TRUE;

        if (day_c <= DEF_ALL_DAYS) {
            size_t check_day = FALSE;
            int leap = ((year_c % 4 == 0 && year_c % 100 != 0) ||
                        (year_c % 400) == 0); // проверка на вис год

            switch (month_c) {
            case APR:  // реализация аналогично case 11
            case JUNE: // реализация аналогично case 11
            case SEPT: // реализация аналогично case 11
            case NOVEM:
                check_day = day_c > DAYS_NOVEM ? TRUE : FALSE;
                break;
            case FEB:
                int check_leap = leap ? FEB_LEAP_T : FEB_LEAP_F;
                check_day = day_c > check_leap ? TRUE : FALSE;
                break;
            default:
                check_day = day_c > DEF_ALL_DAYS ? TRUE : FALSE;
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

err_code incr_str_arr(strs_all *strs, size_t *hw, size_t curr_hw,
                      size_t lenstr) {
    *hw *= 2; // увеличение размера в 2 раза
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

void update_dates(str_inform_t *item, dateStrs new_date) {
    if (cmp_dates(&new_date, item->max_date) > 0) {
        *item->max_date = new_date;
    }
    if (item->min_date->day == BREAK_DATE ||
        cmp_dates(&new_date, item->min_date) < 0) {
        *item->min_date = new_date;
    }
}

void init_date_storage(str_inform_t *item, size_t capacity) {
    item->dates_str = malloc_ptr(sizeof(dateStrs) * capacity);

    if (item->min_date == NULL) {
        item->min_date = malloc_ptr(sizeof(dateStrs));
        item->min_date->day = item->min_date->month = item->min_date->year =
            BREAK_DATE;
    }

    if (item->max_date == NULL) {
        item->max_date = malloc_ptr(sizeof(dateStrs));
        item->max_date->day = item->max_date->month = item->max_date->year =
            BREAK_DATE;
    }
}

void add_date(str_inform_t *item, dateStrs date, size_t *count,
              size_t *capacity) {
    if (*count == *capacity) {
        *capacity *= 2; // увеличение размера в 2 раза
        item->dates_str =
            realloc_ptr(item->dates_str, sizeof(dateStrs) * (*capacity));
    }

    item->dates_str[*count] = date;
    update_dates(item, date);
    (*count)++;
}

err_code parse_dates(str_inform_t *item) {
    char *curr_str = item->str;
    size_t temp_ptr = 0;
    size_t capacity = DATES_D;
    size_t count = 0;

    item->dates_str = NULL;
    item->min_date = NULL;
    item->max_date = NULL;

    init_date_storage(item, capacity);

    while (*curr_str != LINE_BREAK) {
        dateStrs d;
        if (sscanf(curr_str, "%d/%d/%d%ln", &d.day, &d.month, &d.year,
                   &temp_ptr) == 3) {
            curr_str += temp_ptr;

            if (!check_dates(d.day, d.month, d.year)) {
                add_date(item, d, &count, &capacity);
            }
        } else {
            curr_str++;
        }
    }

    if (count == 0) {
        item->inf = TRUE;
        item->date_c = 1; // inf
    } else {
        item->inf = FALSE;
        if (count < capacity) {
            item->dates_str =
                realloc_ptr(item->dates_str, sizeof(dateStrs) * count);
        }
        item->date_c = count;
    }

    return SUCCESS;
}