#include <stdio.h>
#include <stdlib.h>

#include "control.h"
#include "findcntdel.h"
#include "maxmindate.h"
#include "minDate.h"
#include "readaform.h"

void print_sents(strs_all *strs);

int main() {
    fprintf(stdout, "Course work for option 4.8, created by Lev Beizer\n");

    strs_all *strs = (strs_all *)malloc(sizeof(strs_all));

    comms_opts *comm_opt_ptr_t = (comms_opts *)malloc(sizeof(comms_opts));
    if (comm_opt_ptr_t == NULL) {
        fprintf(stdout, "Error: Memory allocation error\n");
        return 0; // по условию ТЗ везде 0 (1)
    }
    comms_opts *comm_opt_ptr = comm_opt_ptr_t;

    size_t inp_oup_ctrl_r = inp_oup_ctrl(comm_opt_ptr);
    if (inp_oup_ctrl_r) {
        return inp_oup_ctrl_r;
    }

    size_t read_a_format_r = 0;
    switch (comm_opt_ptr->opts) {
    case 1:
        read_a_format_r = read_a_format(strs);
        if (read_a_format_r) {
            return read_a_format_r;
        }
        size_t curr_date_r = curr_date(strs);
        if (curr_date_r) {
            return curr_date_r;
        }
        break;
    case 2:
        read_a_format_r = read_a_format(strs);
        if (read_a_format_r) {
            return read_a_format_r;
        }
        size_t findMinDate_r = findMinDate(strs);
        if (findMinDate_r) {
            return findMinDate_r;
        }
        print_sents(strs);
        break;
    case 3:
        read_a_format_r = read_a_format(strs);
        if (read_a_format_r) {
            return read_a_format_r;
        }
        size_t findcntdel_r = find_cnt_del(strs);
        if (findcntdel_r) {
            return findcntdel_r;
        }
        print_sents(strs);
        break;
    case 4:
        read_a_format_r = read_a_format(strs);
        if (read_a_format_r) {
            return read_a_format_r;
        }
        size_t max_min_date_r = max_min_date(strs);
        if (max_min_date_r) {
            return max_min_date_r;
        }
        break;
    case 5:

        break;
    }

    return 0;
}

void print_sents(strs_all *strs) {
    for (size_t i = 0; i < strs->total_len; i++) {
        printf("%s\n", strs->str_a_len[i].str);
    }
}