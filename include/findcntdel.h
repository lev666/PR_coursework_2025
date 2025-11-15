#pragma once

#include "readaform.h"

#include <stdlib.h>

/**
 * @file findcntdel.h
 * @brief Заголовок для исходника findcntdel.c.
 */

/**
 * @brief Объявление функции нахождения вхождения 19 века.
 * 
 * @return Возвращает код состояния @see main()
 * @param strs Входная структура текста.
 * @see @ref funcnum Входная функция под номером 3.
 */
int find_cnt_del(strs_all* strs);