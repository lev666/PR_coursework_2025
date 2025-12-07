#pragma once

#include <stdlib.h>

/**
 * @file readaform.h
 * @brief Заголовок для исходника readaform.c.
 */

/**
 * @brief Структура для хранения даты (день, месяц, год).
 * @note Это typedef для анонимной структуры.
 */
typedef struct {
    int day; /**< День (1-31) */
    int month; /**< Месяц (1-12) */
    int year; /**< Год (1-9999) */
} dateStrs;

/**
 * @brief Структура для хранения информации о строке.
 * @note Это typedef для анонимной структуры.
 */
typedef struct {
    char* str; /**< указатель на строку */
    size_t lenstr; /**< длина строки */

    dateStrs* dates_str; /**< Указатель на все вхождения дат в строку */
    dateStrs* min_date; /**< Указатель на минимальную дату */
    dateStrs* max_date; /**< Указатель на максимальную дату */
    size_t inf; /**< Флаг бесконечности */
    size_t date_c; /**< Количество вхождений дат в строку */

    size_t index_str; /**< Индекс первоначального вхождения предложения (до форматирования) */
} str_inform_t;

/**
 * @brief Структура для хранения информации о строках и их количестве.
 * @note Это typedef для анонимной структуры.
 */
typedef struct {
    char* str_inp; /**< Строка для доп функций */
    str_inform_t* str_inform; /**< Указатель на строки */
    size_t total_len; /**< Количество строк */
} strs_all;

/**
 * @brief Перечисление для bool интерпритации.
 * @note Это typedef для анонимного перечисления.
 */
typedef enum {
    FALSE, /**< <0> */
    TRUE /**< <1> */
} Boolean;

/**
 * @brief Перечисление для состояния кодов возврата.
 * @note Это typedef для анонимного перечисления.
 * @note По ТЗ всегда будет SUCCESS.
 */
typedef enum {
    SUCCESS, /**< <0> */
    ERR_MALLOC, /**< <1> */
    ERR_REALLOC, /**< <2> */
    ERR_INVALID_ARG /**< <3> */
} err_code;

/**
 * @brief Перечисление месяцев для читабельности.
 * @note Это typedef для анонимного перечисления.
 */
typedef enum {
    JAN = 1,
    FEB = 2,
    MARCH = 3,
    APR = 4,
    MAY = 5,
    JUNE = 6,
    JUL = 7,
    AUGS = 8,
    SEPT = 9,
    OCTOB = 10,
    NOVEM = 11,
    DECEM = 12,
} Months;

/**
 * @brief Объявление функции для создания связного списка и заполнения.
 * 
 * @return Возвращает код состояния @see main()
 * @param strs Входная структура текста.
 */
err_code read_a_format(strs_all* strs);

/**
 * @brief Объявление функции для выделения памяти под Dynamic array.
 * 
 * @return Возвращает void указатель.
 * @param size Размер в байтах.
 */
void* malloc_ptr(size_t size);

/**
 * @brief Объявление функции для реаллоцирования памяти под Dynamic array.
 * 
 * @return Возвращает void указатель.
 * @param size Размер в байтах.
 * @param ptr Указатель на Dynamic array.
 */
void* realloc_ptr(void* ptr, size_t size);