#include "sortsents.h"
#include "readaform.h"

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

int check_match(char** words1, int c1, char** words2, int c2) {
    if (c1 != c2) return 0;

    int *used = calloc(c2, sizeof(int));
    int match_c = 0;

    for (int i = 0; i < c1; i++) {
        int found = 0;
        for (int j = 0; j < c2; j++) {
            if (!used[j] && strcasecmp(words1[i], words2[j]) == 0) {
                used[j] = 1;
                found = 1;
                break;
            }
        }
        if (found) match_c++;
    }

    free(used);

    return (c1 == match_c);
}

char* my_strdup(const char* src) {
    if (src == NULL) return NULL;

    size_t len = strlen(src);

    char* dest = (char*)malloc_ptr(sizeof(char) * len + 1);

    memcpy(dest, src, len + 1);

    return dest;
}

ErrCode sortsents(strs_all *strs) {
    int* printed = calloc(strs->total_len, sizeof(int));
    for (size_t i = 0; i < strs->total_len; i++) {
        if (printed[i]) continue;
        char* str1 = my_strdup(strs->str_inform[i].str);
        int capacity_two = 10;
        int capacity_one = 10;

        int c_words1 = 0;
        char** words1 = NULL;
        words1 = malloc_ptr(sizeof(char*) * capacity_one);
        char* pch = strtok(str1, " ,.-");
        while (pch != NULL) {
            if (capacity_one == c_words1) {
                capacity_one *= 2;
                words1 = realloc_ptr(words1, sizeof(char*) * capacity_one);
            }
            words1[c_words1] = pch;
            pch = strtok(NULL, " ,.-");
            c_words1++;
        }
        for (size_t j = i + 1; j < strs->total_len; j++) {
            if (printed[j]) continue;
            char* str2 = my_strdup(strs->str_inform[j].str);

            int c_words2 = 0;
            char** words2 = NULL;
            words2 = malloc_ptr(sizeof(char*) * capacity_two);
            char* pch = strtok(str2, " ,.-");
            while (pch != NULL) {
                if (capacity_two == c_words2) {
                    capacity_two *= 2;
                    words2 = realloc_ptr(words2, sizeof(char*) * capacity_two);
                }
                words2[c_words2] = pch;
                pch = strtok(NULL, " ,.-");
                c_words2++;
            }

            if (check_match(words1, c_words1, words2, c_words2)) {
                printf("%.*s", (int) strlen(strs->str_inform[i].str) - 1, strs->str_inform[i].str);
                printf(" ::: ");
                printf("%.*s", (int) strlen(strs->str_inform[j].str) - 1, strs->str_inform[j].str);
                printf(".\n");

                printed[i] = 1;
                printed[j] = 1;

                free(words1); free(words2); free(str2);
                words1 = NULL;
                break;
            }
            free(words2); free(str2);
        }
        free(str1);
        if (words1 != NULL) {
            free(words1);
        }
    }
    free(printed);
    return SUCCESS;
}