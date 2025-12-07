#include "duplword.h"
#include "readaform.h"

#include <stdio.h>

err_code duplword(strs_all *strs) {
    for (size_t i = 0; i < strs->total_len; i++) {
        char *ptr = strs->str_inform[i].str;

        int word_len = 0;
        int first = 0;
        while (*ptr != '\0') {
            if (*ptr == ' ' && first == 0) {
                printf("%.*s", word_len, ptr - word_len);
                printf(" %.*s", word_len, ptr - word_len);
                first++;
                word_len = 0;
            } else if (*ptr == ' ' && first == 1) {
                printf("%.*s", word_len, ptr - word_len);
                printf("%.*s", word_len, ptr - word_len);
                word_len = 0;
            } else if (*ptr == '.' && first == 1) {
                printf("%.*s", word_len, ptr - word_len);
                printf("%.*s.\n", word_len, ptr - word_len);
                word_len = 0;
            } else if (*ptr == '.' && first == 0) {
                printf("%.*s", word_len, ptr - word_len);
                printf(" %.*s.\n", word_len, ptr - word_len);
            }
            word_len++;
            ptr++;
        }
    }

    return SUCCESS;
}