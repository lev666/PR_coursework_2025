#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "currdate.h"

typedef struct {
    unsigned int opts : 3;
} comms_opts;

unsigned int inp_oup_ctrl(comms_opts* comm_opt);