#include "control.h"
#include "readaform.h"


int main() {
    fprintf(stdout, "Course work for option 4.8, created by Lev Beizer\n");

    comms_opts* comm_opt_ptr = (comms_opts*)malloc(sizeof(comms_opts));
    strs_all* strs = (strs_all*)malloc(sizeof(strs_all));

    if (comm_opt_ptr == NULL) {
        fprintf(stdout, "Error: Memory allocation error\n");
        return 1;
    }

    if (inp_oup_ctrl(comm_opt_ptr) != 0) {
        return 1;
    }
    
    if (read_a_format(strs) != 0) {
        return 1;
    }

    switch (comm_opt_ptr->opts) {
        case 1:
            if (curr_date(strs) != 0) {
                return 1;
            }
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            /* code */
            break;
        case 5:
            /* code */
            break;
        }

    /*
    for (size_t i = 0; i < strs->total_len; i++) {
        printf("%s", strs->str_a_len[i].str);
    }
    */

    return 0;
}