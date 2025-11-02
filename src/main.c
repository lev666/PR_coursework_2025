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
    
    /*
    for (size_t i = 0; i <= strs ->total_len; i++) {
        printf("%s", strs->str_a_len[i].str);
    }
    */
    // curr_date(strs, &temp_wh);

    return 0;
}