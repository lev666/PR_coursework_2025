#include <stdio.h>
#include <stdlib.h>

#include "control.h"

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
