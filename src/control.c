#include "control.h"

unsigned int inp_oup_ctrl(comms_opts* comm_opt) {
    char buffer[5];
    unsigned int temp_comm = -1;
    
    if (fgets(buffer, 5, stdin) != NULL) {
        if (sscanf(buffer, "%d", &temp_comm) == 1) {
            if (temp_comm >= 0 && temp_comm <= 5) {
                comm_opt -> opts = temp_comm;
            } else {
                fprintf(stdout, "Error: incorrect input %d\n", temp_comm); /* Вообще, лучше ошибки выводить в stderr, 
                                                                            но ТЗ требует иное */
                return 1;
            }
        } else {
            fprintf(stdout, "Error: incorrect input\n");
            return 1;
        }
    } else {
        fprintf(stdout, "Error: incorrect input\n");
        return 1;
    }

    return 0;
}
