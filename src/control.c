#include "control.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @file control.c
 * @brief Исходник отвечающий за чтение ввода из stdin.
 */

int inp_oup_ctrl(comms_opts *comm_opt) {
    char buffer[5];
    size_t temp_comm;

    if (fgets(buffer, 5, stdin) != NULL) {
        if (sscanf(buffer, "%ld", &temp_comm) == 1) {
            if (temp_comm <= 5) {
                comm_opt->opts = temp_comm;
            } else {
                fprintf(stdout, "Error: incorrect input %ld\n",
                        temp_comm); /* Вообще, лучше ошибки выводить в stderr,
                                    но ТЗ требует иное */
                return 0;           // (1)
            }
        } else {
            fprintf(stdout, "Error: incorrect input\n");
            return 0;
        }
    } else {
        fprintf(stdout, "Error: incorrect input\n");
        return 0;
    }

    return 0;
}
