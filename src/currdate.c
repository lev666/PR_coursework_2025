#include <stdio.h>
#include "currdate.h"

unsigned int curr_date(strs_all* strs) {
    time_t times = time(0);
    struct tm* curr_time = localtime(&times);

    char form_curr_time[11];
    strftime(form_curr_time, 11, "%d/%m/%Y", curr_time);
    size_t data, mounth, year = 0;
    if (sscanf(form_curr_time, "%d/%d/%d", &data, &mounth, &year) != 3) {
        fprintf(stdout, "Error: string formatt error");
        return 1;
    }

    for (size_t i = 0; i < strs->total_len; i++) {
        char* curr_str = strs->str_a_len[i].str;

        printf("%s", curr_str);
        size_t data_c, mounth_c, year_c = 0;
        size_t temp_ptr = 0;
        while (*curr_str != '\0') {
            if (sscanf(curr_str, "%d/%d/%d%n", &data_c, &mounth_c, &year_c, &temp_ptr) == 3) {
                curr_str += temp_ptr;
                if (data == data_c && mounth == mounth_c && year == year_c) {
                    printf("%s\n", curr_str);
                    break;
                }
            } else {
                curr_str++;
            }
        }
    }

    return 0;
}