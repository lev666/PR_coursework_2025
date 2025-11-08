#pragma once
#include "currdate.h"
#include <stdlib.h>


typedef struct {
    size_t opts : 3;
} comms_opts;

int inp_oup_ctrl(comms_opts* comm_opt);