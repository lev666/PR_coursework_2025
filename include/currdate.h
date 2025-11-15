#pragma once

#include "readaform.h"

#include <stdlib.h>

/**
 * @file currdate.h
 * @brief Заголовок для исходника currdate.c.
 */

/**
 * @brief Объявление функции нахождения предложенией с вхождением текущей даты.
 * 
 * @return Возвращает код состояния @see main()
 * @param strs Входная структура текста.
 * @see @ref funcnum Входная функция под номером 1.
 */
int curr_date(strs_all* strs);