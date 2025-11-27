#include "readaform.h"
#include "splitsents.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int find_word_sep(char* str, int* w_len, int* sep_len) {
    if (str == NULL || *str == '\0') return 0;
    char* temp_ptr = str;
    *w_len = 0;
    while (*temp_ptr != '\0' && (isalnum(*temp_ptr) || *temp_ptr == '-')) {
        (*w_len)++;
        temp_ptr++;
    }

    *sep_len = 0;
    while (*temp_ptr != '\0' && *temp_ptr != '.' && !(isalnum(*temp_ptr) || *temp_ptr == '-')){
        (*sep_len)++;
        temp_ptr++;
    }

    if (*sep_len == 0 && *w_len == 0) return 0;
    
    return 1;
}

ErrCode split_sent(strs_all *strs) {
    char filler[102], sep1[102], sep2[102];
    if (sscanf(strs->str_inp, "%s %s %s", filler, sep1, sep2) != 3) {
        return 1;
    }

    for (size_t i = 0; i < strs->total_len; i += 2) {
        char* ptr1 = strs->str_inform[i].str;
        char* ptr2 = (i + 1 < strs->total_len) ? strs->str_inform[i + 1].str : NULL;

        int words_ind = 0;
        while ((ptr1 && *ptr1 != '\0') || (ptr2 && *ptr2 != '\0')) {
            int w1_len = 0, w2_len = 0;
            int sep1_str_len = 0, sep2_str_len = 0;

            int has_w1 = find_word_sep(ptr1, &w1_len, &sep1_str_len);
            int has_w2 = find_word_sep(ptr2, &w2_len, &sep2_str_len);
            char* sep1_str = ptr1 + w1_len;
            char* sep2_str = ptr2 + w2_len;

            int dot1 = 0, dot2 = 0;
            if (ptr1[w1_len + sep1_str_len] == '.') dot1 = 1;
            if ((has_w2) && (ptr2[w2_len + sep2_str_len] == '.')) dot2 = 1;

            char* curr_sep = (words_ind % 2 == 0) ? sep1 : sep2;

            if (has_w1) printf("%.*s", w1_len, ptr1);
            else printf("%s", filler);

            printf("%s", curr_sep);

            if (has_w2) printf("%.*s", w2_len, ptr2);
            else printf("%s", filler);

            if (sep1_str) printf("%.*s", sep1_str_len, sep1_str);
            if (sep2_str) printf("%.*s", sep2_str_len, sep2_str);

            int check_left = (!has_w1) || dot1;
            int check_right = (!has_w2) || dot2;
            if ((dot1 || dot2) && check_left && check_right) {
                printf(".");
            }

            if (has_w1) ptr1 += w1_len + sep1_str_len + dot1;
            if (has_w2) ptr2 += w2_len + sep2_str_len + dot2;

            words_ind++;
        }
        printf("\n");
    }
    
    return SUCCESS;
}