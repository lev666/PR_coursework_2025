#include <stdio.h>
#include <stdlib.h>

#include "control.h"
#include "minDate.h"
#include "findcntdel.h"
#include "readaform.h"

void print_sents(strs_all* strs);

int main() {
  fprintf(stdout, "Course work for option 4.8, created by Lev Beizer\n");

  strs_all *strs = (strs_all *)malloc(sizeof(strs_all));

  comms_opts *comm_opt_ptr_t = (comms_opts *)malloc(sizeof(comms_opts));
  if (comm_opt_ptr_t == NULL) {
    fprintf(stdout, "Error: Memory allocation error\n");
    return 1;
  }
  comms_opts *comm_opt_ptr = comm_opt_ptr_t;

  size_t inp_oup_ctrl_r = inp_oup_ctrl(comm_opt_ptr);
  if (inp_oup_ctrl_r != 0) {
    return inp_oup_ctrl_r;
  }

  size_t read_a_format_r = read_a_format(strs);
  if (read_a_format_r != 0) {
    return read_a_format_r;
  }

  switch (comm_opt_ptr->opts) {
  case 1:
    size_t curr_date_r = curr_date(strs);
    if (curr_date_r != 0) {
      return curr_date_r;
    }
    break;
  case 2:
    size_t findMinDate_r = findMinDate(strs);
    if (findMinDate_r != 0) {
      return findMinDate_r;
    }
    print_sents(strs);
    break;
  case 3:
    size_t findcntdel_r = find_cnt_del(strs);
    if (findcntdel_r != 0) {
      return findcntdel_r;
    }
    print_sents(strs);
    break;
  case 4:
    /* code */
    break;
  case 5:
    /* code */
    break;
  }

  return 0;
}

void print_sents(strs_all* strs) {
    for (size_t i = 0; i < strs->total_len; i++) {
        printf("%s\n", strs->str_a_len[i].str);
    }
}