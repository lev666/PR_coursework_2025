#pragma once

#include "readaform.h"

#include <stdlib.h>

/**
 * @file minDate.h
 * @brief Заголовок для исходника minDate.c.
 */

/**
 * @brief Объявление функции сортировки предложений по min дате.
 * 
 * @return Возвращает код состояния @see main()
 * @param strs Входная структура текста.
 * @see @ref funcnum Входная функция под номером 2.
 */
ErrCode findMinDate(strs_all* strs);