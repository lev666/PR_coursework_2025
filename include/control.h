#pragma once

#include "currdate.h"

#include <stdlib.h>

/**
 * @file control.h
 * @brief Заголовок для исходника control.c.
 */

/**
 * @brief Структура для хранения информации об номере команды (в битовом поле).
 * @note Это typedef для анонимной структуры.
 */
typedef struct {
    size_t opts : 4; /**< Номер функции (до 9 максимум) */
} comms_opts;

/**
 * @brief Объявление функции для чтения ввода из stdin.
 * 
 * @return Возвращает код состояния @see main()
 * @param comm_opt Входная структура хранения номера функции.
 * @see @ref funcnum Допустимые значения.
 */
int inp_oup_ctrl(comms_opts* comm_opt);