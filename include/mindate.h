#pragma once

#include "readaform.h"

#include <stdlib.h>

/**
 * @file mindate.h
 * @brief Заголовок для исходника mindate.c.
 */

/**
 * @brief Объявление функции сортировки предложений по min дате.
 * 
 * @return Возвращает код состояния @see main()
 * @param strs Входная структура текста.
 * @see @ref funcnum Входная функция под номером 2.
 */
err_code find_min_date(strs_all* strs);