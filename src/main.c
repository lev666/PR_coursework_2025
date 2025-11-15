#include <stdio.h>
#include <stdlib.h>

#include "control.h"
#include "findcntdel.h"
#include "maxmindate.h"
#include "minDate.h"
#include "readaform.h"

#define MEMFREEFAIL "Error: Memory is not free\n"

#define BLUE "\033[1;34m" /**< Синий цвет форматирования */
#define RESETCOLOR "\033[0m" /**< Возврат цвета */

/**
 * @file main.c
 * @brief Является корнем программы и вызовом основных функций.
 */

/**
 * @brief Объявление функции вывода строк.
 *
 * @param strs Входная структура текста.
 */
void print_sents(strs_all *strs);

/**
 * @brief Объявление функции вызова справочной информации.
*/
void help_comm();

/**
 * @brief Объявление функции свобождения памяти.
 * 
 * @param strs Входная структура текста.
 * @return Код возврата состояния.
 * @see main()
 */
int free_strs(strs_all* strs);

/**
 * @brief Главная функция исполнения.
 *
 * @return Код возврата состояния. (по ТЗ он 0)
 * @note По ТЗ код возврата всегда 0, но лучше иная обарботка (0, 1...).
 */
int main() {
    fprintf(stdout, "Course work for option 4.8, created by Lev Beizer\n");

    strs_all *strs = NULL;

    comms_opts *comm_opt_ptr_t = (comms_opts *)malloc(sizeof(comms_opts));
    if (comm_opt_ptr_t == NULL) {
        fprintf(stdout, "Error: Memory allocation error\n");
        return 0;
    }
    comms_opts *comm_opt_ptr = comm_opt_ptr_t;

    size_t inp_oup_ctrl_r = inp_oup_ctrl(comm_opt_ptr);
    if (inp_oup_ctrl_r) {
        return inp_oup_ctrl_r;
    }

    size_t command = comm_opt_ptr->opts;

    if (command > 0 && command < 5) {
        strs = (strs_all *)malloc(sizeof(strs_all));
        if (strs == NULL) {
            fprintf(stdout, "Error: Memory allocation error\n");
            return 0;
        }
        size_t read_a_format_r = read_a_format(strs);
        if (read_a_format_r) {
            return read_a_format_r;
        }
    }

    switch (comm_opt_ptr->opts) {
    case 1:
        size_t curr_date_r = curr_date(strs);
        if (curr_date_r) {
            return curr_date_r;
        }
        break;
    case 2:
        size_t findMinDate_r = findMinDate(strs);
        if (findMinDate_r) {
            return findMinDate_r;
        }
        print_sents(strs);
        break;
    case 3:
        size_t findcntdel_r = find_cnt_del(strs);
        if (findcntdel_r) {
            return findcntdel_r;
        }
        print_sents(strs);
        break;
    case 4:
        size_t max_min_date_r = max_min_date(strs);
        if (max_min_date_r) {
            return max_min_date_r;
        }
        break;
    case 5:
        help_comm();
        break;
    }

    if (command != 5) {
        size_t free_strs_r = free_strs(strs);
        if (free_strs_r) return free_strs_r;
    }

    return 0;
}

void print_sents(strs_all *strs) {
    for (size_t i = 0; i < strs->total_len; i++) {
        printf("%s\n", strs->str_a_len[i].str);
    }
}

void help_comm() {
    printf("%1$sКоманды от 1 до 5:%2$s\n\n"
         "  %1$s1%2$s\n"
         "Все предложения в которых есть дата с текущим годом и\n"
         "месяцем. (дата записывается в формате DD/MM/YYYY)\n\n"
         "  %1$s2%2$s\n"
         "Отсортированые предложения по увеличению минимальной даты в них.\n"
         "Если в предложении нет даты, то следует считать, что 'мнимая\n"
         "минимальная дата' == inf. В случае равенства сохранить порядок\n"
         "вхождения.\n\n"
         "  %1$s3%2$s\n"
         "Удалить все предложения в которых все даты относятся к 19 веку.\n\n"
         "  %1$s4%2$s\n"
         "Для каждого предложения выводит самую раннюю и позднюю дату.\n"
         "Предложения не выводятся, только строки в формате:"
         "'Earliest date: <date>' и 'Latest date: <date>'.\n\n"
         "  %1$s5%2$s\n"
         "Справка об функциях исполняемой программы.\n", BLUE, RESETCOLOR);
}

int free_strs(strs_all* strs) {
    if (strs != NULL && strs->str_a_len != NULL) {
        for (size_t i = 0; i < strs->total_len; i++) {
            free(strs->str_a_len[i].str);
            free(strs->str_a_len[i].dates_str);
            free(strs->str_a_len[i].minDate);
            free(strs->str_a_len[i].maxDate);
        }
        free(strs->str_a_len);
        free(strs);
    }

    return 0;
}