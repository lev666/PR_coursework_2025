#pragma once

#include "readaform.h"

#include <stdlib.h>

/**
 * @file maxmindate.h
 * @brief Заголовок для исходника maxmindate.c.
 */

 /**
 * @brief Объявление функции нахождения поздней и ранней даты.
 * 
 * @return Возвращает код состояния @see main()
 * @param strs Входная структура текста.
 * @see @ref funcnum Входная функция под номером 4.
 */
ErrCode max_min_date(strs_all* strs);