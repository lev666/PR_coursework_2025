#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

#include "readaform.h"

int cmp_dates(const dateStrs* ptr1, const dateStrs* ptr2);

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
            strs->total_len = hw;

            for (size_t j = curr_hw; j < hw; j++) {
                char* temp6 = (char*)malloc(sizeof(char) * lenstr);
                if (temp6 == NULL) {
                    fprintf(stdout, "Error: Memory allocation error\n");
                    return 1;
                }
                strs->str_a_len[j].str = temp6;
            }

        }

        if (curr_lenstr + 1 == lenstr) {
            lenstr *= 2;
            char* temp4 = (char*)realloc(strs->str_a_len[curr_hw].str, sizeof(char) * lenstr);
            if (temp4 == NULL) {
                    fprintf(stdout, "Error: Memory allocation error\n");
                    return 1;
            } 
            strs->str_a_len[curr_hw].str = temp4;
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
                strs->str_a_len[curr_hw].index_str = curr_hw;

                unsigned int day_c, mounth_c, year_c = 0;
                size_t temp_ptr = 0;

                size_t capacity = 5;

                strs->str_a_len[curr_hw].curr_date_str = (dateStrs*)malloc(sizeof(dateStrs) * capacity);
                if (strs->str_a_len[curr_hw].curr_date_str == NULL) { // исправь корректную обработку 
                    fprintf(stdout, "Error: Memory allocation error\n");
                    return 1;
                }
                if (strs->str_a_len[curr_hw].minDate == NULL) {
                    dateStrs* tempss = (dateStrs*)malloc(sizeof(dateStrs));
                    if (tempss == NULL) {
                        fprintf(stdout, "Error: Memory allocation error\n");
                        return 1;
                    }
                    strs->str_a_len[curr_hw].minDate = tempss;
                    strs->str_a_len[curr_hw].minDate->day = 0;
                    strs->str_a_len[curr_hw].minDate->month = 0;
                    strs->str_a_len[curr_hw].minDate->year = 0;
                }
                size_t* minDay = &(strs->str_a_len[curr_hw].minDate->day);
                size_t* minMonth = &(strs->str_a_len[curr_hw].minDate->month);
                size_t* minYear = &(strs->str_a_len[curr_hw].minDate->year);
                size_t* minInf = &(strs->str_a_len[curr_hw].minDate->inf);

                size_t count_dates_str = 0;

                while (*curr_str != '\0') {
                    if (sscanf(curr_str, "%d/%d/%d%n", &day_c, &mounth_c, &year_c, &temp_ptr) == 3) {
                        curr_str += temp_ptr;
                        if (count_dates_str == capacity) { // исправь корр обр
                            capacity *= 2;
                            strs->str_a_len[curr_hw].curr_date_str = (dateStrs*)realloc(strs->str_a_len[curr_hw].curr_date_str, sizeof(dateStrs) * capacity);
                        }
                        
                        if (*minDay == 0 && *minMonth == 0 && *minYear == 0) {
                            *minDay = day_c;
                            *minMonth = mounth_c;
                            *minYear = year_c;
                        } else if (cmp_dates(&(strs->str_a_len[curr_hw].curr_date_str[count_dates_str]), strs->str_a_len[curr_hw].minDate) < 0) {
                            *minDay = day_c;
                            *minMonth = mounth_c;
                            *minYear = year_c;  
                        }
                        strs->str_a_len[curr_hw].curr_date_str[count_dates_str].day = day_c;
                        strs->str_a_len[curr_hw].curr_date_str[count_dates_str].month = mounth_c;
                        strs->str_a_len[curr_hw].curr_date_str[count_dates_str].year = year_c;
                        count_dates_str++;

                        day_c, mounth_c, year_c = 0;
                    } else {
                        curr_str++;
                    }
                }

                if (count_dates_str == 0) {
                    strs->str_a_len[curr_hw].curr_date_str->inf = 1;
                    *minInf = 1;
                    *minDay = 0;
                    *minMonth = 0;
                    *minYear = 0;
                    strs->str_a_len[curr_hw].date_c = 1;
                } else {
                    strs->str_a_len[curr_hw].curr_date_str->inf = 0;
                    if (count_dates_str < capacity) {
                        dateStrs* temp3 = (dateStrs*)realloc(strs->str_a_len[curr_hw].curr_date_str, sizeof(dateStrs) * count_dates_str);
                        if (temp3 == NULL) {
                            fprintf(stdout, "Error: Memory allocation error\n");
                            return 1;
                        }
                        strs->str_a_len[curr_hw].curr_date_str = temp3;
                    }
                    strs->str_a_len[curr_hw].date_c = count_dates_str;
                }
                curr_hw++;
            }
            lenstr = 30;
            curr_lenstr = 0;
        }
    }

    if (curr_hw < hw) {
        strsalen* temps = (strsalen*)realloc(strs->str_a_len, sizeof(strsalen) * curr_hw);
        if (temps == NULL && curr_hw > 0) {
            fprintf(stdout, "Error: Memory allocation error\n");
            return 1;
        }
        strs->str_a_len = temps;
    }
    strs->total_len = curr_hw;

    return 0;
}

int cmp_dates(const dateStrs* ptr1, const dateStrs* ptr2) {
    const size_t day_p1 = ptr1->day;
    const size_t month_p1 = ptr1->month;
    const size_t year_p1 = ptr1->year;
    const size_t day_p2 = ptr2->day;
    const size_t month_p2 = ptr2->month;
    const size_t year_p2 = ptr2->year;

    if (year_p1 != year_p2) {
        return year_p1 - year_p2;
    } else if (month_p1 != month_p2) {
        return month_p1 - month_p2;
    } else if (day_p1 != day_p2) {
        return day_p1 - day_p2;
    }

    return 0;
}