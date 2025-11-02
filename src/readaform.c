#include <ctype.h>
#include <stdlib.h>

#include "readaform.h"

unsigned int read_a_format(strs_all* strs) {
    size_t hw = 5;
    size_t lenstr = 30;
    strs->str_a_len = (strsalen*)malloc(sizeof(strsalen) * hw);

    if (strs->str_a_len == NULL) {
        fprintf(stdout, "Error: Memory allocation error\n");
        return 1;
    }

    for (size_t k = 0; k < hw; k++) {
        strs->str_a_len[k].str = (char*)malloc(sizeof(char) * lenstr);
    }

    char c;
    size_t curr_hw = 0;
    size_t curr_lenstr = 0;
    size_t check_end = 0;

    while (((c = fgetc(stdin)) != EOF) && (check_end != 2)) {
        if (check_end == 1) {
            if (c == '\n') {
                check_end++;
                continue;
            } else {
                check_end = 0;
            }
        }
        
        if (c == '\n') {
            check_end++;
            continue;
        }

        if (curr_hw == hw) {
            hw *= 2;
            strsalen* temp = (strsalen*)realloc(strs->str_a_len, sizeof(strsalen) * hw);
            if (temp == NULL) {
                    fprintf(stdout, "Error: Memory allocation error\n");
                    return 1;
            }
            strs->str_a_len = temp;

        }

        if (curr_lenstr == lenstr) {
            lenstr *= 2;
            char* temp = (char*)realloc(strs->str_a_len[curr_hw].str, sizeof(char) * lenstr);
            if (temp == NULL) {
                    fprintf(stdout, "Error: Memory allocation error\n");
                    return 1;
            } 
            strs->str_a_len -> str = temp;
            strs->str_a_len -> lenstr = lenstr;
        }

        if (c != '.') {
            strs->str_a_len[curr_hw].str[curr_lenstr++] = c;
        } else {
            strs->str_a_len[curr_hw].str[curr_lenstr++] = c;
            strs->str_a_len[curr_hw++].str[curr_lenstr] = '\0';
            curr_lenstr = 0;
            lenstr = 30;
        }
    }

    if (curr_hw < hw) {
        strsalen* temp = (strsalen*)realloc(strs->str_a_len, sizeof(strsalen) * curr_hw);
        if (temp == NULL) {
            fprintf(stdout, "Error: Memory allocation error\n");
            return 1;
        }
        strs->str_a_len = temp;
        strs->total_len = curr_hw;
    }

    return 0;
}