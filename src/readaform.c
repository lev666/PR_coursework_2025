#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

#include "readaform.h"

unsigned int read_a_format(strs_all* strs) {
    size_t hw = 5;
    size_t lenstr = 30;
    strsalen* temp = (strsalen*)malloc(sizeof(strsalen) * hw);

    if (temp == NULL) {
        fprintf(stdout, "Error: Memory allocation error\n");
        return 1;
    }
    strs->str_a_len = temp;

    for (size_t k = 0; k < hw; k++) {
        char* temp_str = (char*)malloc(sizeof(char) * lenstr);
        if (temp_str == NULL) {
            fprintf(stdout, "Error: Memory allocation error\n");
            return 1;
        }
        strs->str_a_len[k].str = temp_str;
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
            strsalen* temp2 = (strsalen*)realloc(strs->str_a_len, sizeof(strsalen) * hw);
            if (temp2 == NULL) {
                    fprintf(stdout, "Error: Memory allocation error\n");
                    return 1;
            }
            strs->str_a_len = temp2;

        }

        if (curr_lenstr == lenstr) {
            lenstr *= 2;
            char* temp = (char*)realloc(strs->str_a_len[curr_hw].str, sizeof(char) * lenstr);
            if (temp == NULL) {
                    fprintf(stdout, "Error: Memory allocation error\n");
                    return 1;
            } 
            strs->str_a_len -> str = temp;
            strs->str_a_len[curr_hw].lenstr = lenstr;
        }


        if (c != '.') {
            strs->str_a_len[curr_hw].str[curr_lenstr++] = c;
        } else {
            strs->str_a_len[curr_hw].str[curr_lenstr++] = c;
            strs->str_a_len[curr_hw].str[curr_lenstr] = '\0';
            strs->str_a_len[curr_hw].lenstr = lenstr;
            size_t duplc = 0;
            for (size_t k = 0; k < curr_hw; k++) {
                if (lenstr != strs->str_a_len[k].lenstr) {
                    continue;
                }

                if (strcasecmp(strs->str_a_len[curr_hw].str, strs->str_a_len[k].str) == 0) {
                    duplc = 1;
                    free(strs->str_a_len[curr_hw].str);
                    strs->str_a_len[curr_hw].lenstr = 0;
                    char* temp_str2 = (char*)malloc(sizeof(char) * 30); // по умолчанию 30 для всех строк
                    if (temp_str2 == NULL) {
                        fprintf(stdout, "Error: Memory allocation error\n");
                        return 1;
                    }
                    strs->str_a_len[curr_hw].str = temp_str2;
                }
            }

            if (duplc != 1) {
                char* curr_str = strs->str_a_len[curr_hw].str;

                size_t data_c, mounth_c, year_c = 0;
                size_t temp_ptr = 0;

                strs->str_a_len[curr_hw].curr_date_str = (dateStrs*)malloc(sizeof(dateStrs));
                if (strs->str_a_len[curr_hw].curr_date_str == NULL) { // исправь корректную обработку 
                    fprintf(stdout, "Error: Memory allocation error\n");
                    return 1;
                }
                size_t count_dates_str = 0;
                size_t capacity = 5;

                while (*curr_str != '\0') {
                    if (sscanf(curr_str, "%d/%d/%d%n", &data_c, &mounth_c, &year_c, &temp_ptr) == 3) {
                        curr_str += temp_ptr;
                        if (count_dates_str == capacity) { // исправь корр обр
                            capacity *= 2;
                            strs->str_a_len[curr_hw].curr_date_str = (dateStrs*)realloc(strs->str_a_len[curr_hw].curr_date_str, sizeof(dateStrs) * capacity);
                        }
                        
                        strs->str_a_len[curr_hw].curr_date_str[count_dates_str].day = data_c;
                        strs->str_a_len[curr_hw].curr_date_str[count_dates_str].month = mounth_c;
                        strs->str_a_len[curr_hw].curr_date_str[count_dates_str].year = year_c;
                        count_dates_str++;

                        data_c, mounth_c, year_c = 0;
                    } else {
                        curr_str++;
                    }
                }
                if (count_dates_str == 0) {
                    strs->str_a_len[curr_hw].curr_date_str->inf = 1;
                } else {
                    if (count_dates_str < capacity) {
                        strsalen* temp = (strsalen*)realloc(strs->str_a_len[curr_hw].curr_date_str, sizeof(dateStrs) * count_dates_str);
                        if (temp == NULL) {
                            fprintf(stdout, "Error: Memory allocation error\n");
                            return 1;
                        }
                        strs->str_a_len[curr_hw].curr_date_str = temp;
                        strs->str_a_len[curr_hw].date_c = count_dates_str;
                    } else {
                        strs->str_a_len[curr_hw].date_c = count_dates_str;
                    }
                }     
                curr_hw++;
            }
            lenstr = 30;
            curr_lenstr = 0;
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