#include "readaform.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define LENSTR_D 30
#define HW_D 5
#define MEMFAIL "Error: Memory allocation error\n"

int check_dates(int day_c, int month_c, int year_c);

int incr_str_arr(strs_all *strs, size_t *hw, size_t curr_hw, size_t lenstr);

int cmp_dates(const dateStrs *ptr1, const dateStrs *ptr2);

void *malloc_ptr(size_t size);

void *realloc_ptr(void *ptr, size_t size);

int read_a_format(strs_all *strs) {
    size_t hw = HW_D;
    size_t lenstr = LENSTR_D;

    strs->str_a_len = malloc_ptr(sizeof(strsalen) * hw);

    for (size_t k = 0; k < hw; k++) {
        strs->str_a_len[k].str = malloc_ptr(sizeof(char) * lenstr);
    }

    char c;
    size_t curr_hw = 0;
    size_t curr_lenstr = 0;
    size_t check_end = 0;
    size_t check_char = 0;

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
            size_t incr_str_arr_r = incr_str_arr(strs, &hw, curr_hw, lenstr);
            if (incr_str_arr_r != 0)
                return incr_str_arr_r;
        }

        if (curr_lenstr + 1 == lenstr) {
            lenstr *= 2;
            strs->str_a_len[curr_hw].str = realloc_ptr(
                strs->str_a_len[curr_hw].str, sizeof(char) * lenstr);
        }

        char *str_prs = strs->str_a_len[curr_hw].str;
        strsalen *stralen_p = strs->str_a_len;

        if (c != '.') {
            if (!isalnum(c) && c != '-' && check_char == 0) {
                continue;
            } else {
                check_char = 1;
            }
            str_prs[curr_lenstr++] = c;
        } else {
            str_prs[curr_lenstr++] = c;
            str_prs[curr_lenstr] = '\0';
            stralen_p[curr_hw].lenstr = lenstr;
            check_char = 0;
            size_t duplc = 0;
            for (size_t k = 0; k < curr_hw; k++) {
                if (lenstr != stralen_p[k].lenstr)
                    continue;

                if (strcasecmp(str_prs, stralen_p[k].str) == 0) {
                    duplc = 1;
                    free(strs->str_a_len[curr_hw].str);
                    strs->str_a_len[curr_hw].lenstr = 0;
                    strs->str_a_len[curr_hw].str =
                        malloc_ptr(sizeof(char) * LENSTR_D);
                }
            }

            if (duplc != 1) {
                char *curr_str = str_prs;
                size_t *idx_str = &(stralen_p[curr_hw].index_str);
                *idx_str = curr_hw;

                int dayCurr_str, monthCurr_str, yearCurr_str = 0;
                size_t temp_ptr = 0;

                size_t capacity_dates = 5;

                stralen_p[curr_hw].curr_date_str =
                    malloc_ptr(sizeof(dateStrs) * capacity_dates);

                int *minDay_str, *minMonth_str, *minYear_str = NULL;
                int *maxDay_str, *maxMonth_str, *maxYear_str = NULL;

                size_t *inf_str = &(stralen_p[curr_hw].inf);
                if (stralen_p[curr_hw].minDate == NULL) {
                    stralen_p[curr_hw].minDate = malloc_ptr(sizeof(dateStrs));

                    minDay_str = &(stralen_p[curr_hw].minDate->day);
                    minMonth_str = &(stralen_p[curr_hw].minDate->month);
                    minYear_str = &(stralen_p[curr_hw].minDate->year);

                    *minDay_str = *minMonth_str = *minYear_str = -1;
                }
                if (stralen_p[curr_hw].maxDate == NULL) {
                    stralen_p[curr_hw].maxDate = malloc_ptr(sizeof(dateStrs));

                    maxDay_str = &(stralen_p[curr_hw].maxDate->day);
                    maxMonth_str = &(stralen_p[curr_hw].maxDate->month);
                    maxYear_str = &(stralen_p[curr_hw].maxDate->year);

                    *maxDay_str = *maxMonth_str = *maxYear_str = -1;
                }

                size_t count_dates_str = 0;

                dateStrs *currDates_p = stralen_p[curr_hw].curr_date_str;
                while (*curr_str != '\0') {
                    if (sscanf(curr_str, "%d/%d/%d%ln", &dayCurr_str,
                               &monthCurr_str, &yearCurr_str, &temp_ptr) == 3) {
                        curr_str += temp_ptr;

                        if (check_dates(dayCurr_str, monthCurr_str,
                                        yearCurr_str))
                            continue;

                        if (count_dates_str == capacity_dates) {
                            capacity_dates *= 2;
                            stralen_p[curr_hw].curr_date_str = realloc_ptr(
                                currDates_p, sizeof(dateStrs) * capacity_dates);
                            currDates_p = stralen_p[curr_hw].curr_date_str;
                        }

                        if (cmp_dates(&(currDates_p[count_dates_str]),
                                      stralen_p[curr_hw].maxDate) > 0) {
                            *maxDay_str = dayCurr_str;
                            *maxMonth_str = monthCurr_str;
                            *maxYear_str = yearCurr_str;
                        }
                        if (*minDay_str == -1 && *minMonth_str == -1 &&
                            *minYear_str == -1) {
                            *minDay_str = dayCurr_str;
                            *minMonth_str = monthCurr_str;
                            *minYear_str = yearCurr_str;
                        } else if (cmp_dates(&(currDates_p[count_dates_str]),
                                             stralen_p[curr_hw].minDate) < 0) {
                            *minDay_str = dayCurr_str;
                            *minMonth_str = monthCurr_str;
                            *minYear_str = yearCurr_str;
                        }
                        currDates_p[count_dates_str].day = dayCurr_str;
                        currDates_p[count_dates_str].month = monthCurr_str;
                        currDates_p[count_dates_str].year = yearCurr_str;
                        count_dates_str++;

                        dayCurr_str = monthCurr_str = yearCurr_str = 0;
                    } else {
                        curr_str++;
                    }
                }

                if (count_dates_str == 0) {
                    stralen_p[curr_hw].inf = 1;
                    *inf_str = 1;
                    *minDay_str = *minMonth_str = *minYear_str = -1;
                    stralen_p[curr_hw].date_c = 1;
                } else {
                    stralen_p[curr_hw].inf = 0;
                    if (count_dates_str < capacity_dates) {
                        stralen_p[curr_hw].curr_date_str = realloc_ptr(
                            currDates_p, sizeof(dateStrs) * count_dates_str);
                        currDates_p = stralen_p[curr_hw].curr_date_str;
                    }
                    stralen_p[curr_hw].date_c = count_dates_str;
                }
                curr_hw++;
            }
            lenstr = 30;
            curr_lenstr = 0;
        }
    }

    if (curr_hw < hw) {
        strs->str_a_len =
            realloc_ptr(strs->str_a_len, sizeof(strsalen) * curr_hw);
    }
    size_t *totallen = &(strs->total_len);
    *totallen = curr_hw;

    return 0;
}

int check_dates(int day_c, int month_c, int year_c) {
    if (day_c > 0 && month_c > 0 && year_c > 0) {
        if (month_c > 12 || day_c > 31)
            return 1;

        if (day_c < 31) {
            size_t check_day = 0;
            int leap = ((year_c % 4 == 0 && year_c % 100 != 0) ||
                        (year_c % 400) == 0); // проверка на вис год

            switch (month_c) {
            case 4:
            case 6:
            case 9:
            case 11:
                check_day = day_c > 30 ? 1 : 0;
                break;
            case 2:
                int check_leap = leap ? 29 : 28;
                check_day = day_c > check_leap ? 1 : 0;
                break;
            default:
                check_day = day_c > 31 ? 1 : 0;
            }

            if (check_day)
                return 1;
        } else
            return 1;
    }

    return 0;
}

void *malloc_ptr(size_t size) {
    void *temp_ptr = (void *)malloc(size);
    if (temp_ptr == NULL) {
        fprintf(stdout, MEMFAIL);
        exit(EXIT_FAILURE);
    }
    return temp_ptr;
}

void *realloc_ptr(void *ptr, size_t size) {
    void *temp_ptr = (void *)realloc(ptr, size);
    if (temp_ptr == NULL) {
        fprintf(stdout, MEMFAIL);
        exit(EXIT_FAILURE);
    }
    return temp_ptr;
}

int incr_str_arr(strs_all *strs, size_t *hw, size_t curr_hw, size_t lenstr) {
    *hw *= 2;
    strs->str_a_len = realloc_ptr(strs->str_a_len, sizeof(strsalen) * (*hw));
    strs->total_len = (*hw);

    for (size_t j = curr_hw; j < (*hw); j++) {
        strs->str_a_len[j].str = malloc_ptr(sizeof(char) * lenstr);
    }

    return 0;
}

int cmp_dates(const dateStrs *ptr1, const dateStrs *ptr2) {
    if (ptr1->year != ptr2->year) {
        return ptr1->year - ptr2->year;
    } else if (ptr1->month != ptr2->month) {
        return ptr1->month - ptr2->month;
    } else if (ptr1->day != ptr2->day) {
        return ptr1->day - ptr2->day;
    }

    return 0;
}