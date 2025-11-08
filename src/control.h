#pragma once
#include "currdate.h"

typedef struct {
    size_t opts : 3;
} comms_opts;

unsigned int inp_oup_ctrl(comms_opts* comm_opt);