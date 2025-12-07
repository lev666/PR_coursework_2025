#include "control.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_OPTS 5
#define INCR_INP "Error: incorrect input\n"

/**
 * @file control.c
 * @brief Исходник отвечающий за чтение ввода из stdin.
 */

void print_err();

err_code inp_oup_ctrl(comms_opts *comm_opt) {
    char buffer[BUFFER_OPTS];
    size_t temp_comm;

    if (fgets(buffer, BUFFER_OPTS, stdin) != NULL) {
        if (sscanf(buffer, "%ld", &temp_comm) == 1) {
            if (temp_comm < 10 && temp_comm != 6) {
                comm_opt->opts = temp_comm;
            } else {
                fprintf(stdout, "Error: incorrect input %ld\n",
                        temp_comm); /* Вообще, лучше ошибки выводить в
                                    stderr/log, но ТЗ требует иное */
                return SUCCESS;     // (1)
            }
        } else {
            print_err();
            return SUCCESS;
        }
    } else {
        print_err();
        return SUCCESS;
    }

    return SUCCESS;
}

void print_err() { fprintf(stdout, INCR_INP); }