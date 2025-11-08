#include "readaform.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define LENSTR_D 30
#define HW_D 5
#define MEMFAIL "Error: Memory allocation error\n"

int dupl_rows(strs_all *strs, size_t curr_hw);

int incr_str_len_arr(strs_all *strs, size_t curr_hw, size_t *lenstr);

int arr_trunc(strs_all *strs, size_t curr_hw);

int incr_str_arr(strs_all *strs, size_t *hw, size_t curr_hw, size_t lenstr);

int cmp_dates(const dateStrs *ptr1, const dateStrs *ptr2);

int read_a_format(strs_all *strs) {
    size_t hw = HW_D;
    size_t lenstr = LENSTR_D;

    strsalen *temp_hw_f = (strsalen *)malloc(sizeof(strsalen) * hw);
    if (temp_hw_f == NULL) {
        fprintf(stdout, MEMFAIL);
        return 1;
    }
    strs->str_a_len = temp_hw_f;

    for (size_t k = 0; k < hw; k++) {
        char *temp_str_f = (char *)malloc(sizeof(char) * lenstr);
        if (temp_str_f == NULL) {
            fprintf(stdout, MEMFAIL);
            return 1;
        }
        strs->str_a_len[k].str = temp_str_f;
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
            size_t incr_str_arr_r = incr_str_arr(strs, &hw, curr_hw, lenstr);
            if (incr_str_arr_r != 0) {
                return incr_str_arr_r;
            }
        }

        if (curr_lenstr + 1 == lenstr) {
            size_t incr_str_len_arr_r =
                incr_str_len_arr(strs, curr_hw, &lenstr);
            if (incr_str_len_arr_r != 0) {
                return incr_str_len_arr_r;
            }
        }

        char *str_prs = strs->str_a_len[curr_hw].str;
        strsalen *stralen_p = strs->str_a_len;
        if (c != '.') {
            str_prs[curr_lenstr++] = c;
        } else {
            str_prs[curr_lenstr++] = c;
            str_prs[curr_lenstr] = '\0';
            stralen_p[curr_hw].lenstr = lenstr;
            size_t duplc = 0;
            for (size_t k = 0; k < curr_hw; k++) {
                if (lenstr != stralen_p[k].lenstr) {
                    continue;
                }

                if (strcasecmp(str_prs, stralen_p[k].str) == 0) {
                    duplc = 1;
                    size_t dupl_rows_r = dupl_rows(strs, curr_hw);
                    if (dupl_rows_r != 0) {
                        return dupl_rows_r;
                    }
                }
            }

            if (duplc != 1) {
                char *curr_str = str_prs;
                size_t *idx_str = &(stralen_p[curr_hw].index_str);
                *idx_str = curr_hw;

                unsigned int day_c, mounth_c, year_c = 0;
                size_t temp_ptr = 0;

                size_t capacity_dates = 5;

                dateStrs *curr_dates_p_t =
                    (dateStrs *)malloc(sizeof(dateStrs) * capacity_dates);
                if (curr_dates_p_t == NULL) {
                    fprintf(stdout, MEMFAIL);
                    return 1;
                }
                stralen_p[curr_hw].curr_date_str = curr_dates_p_t;

                int *minDay, *minMonth, *minYear = NULL;
                int *maxDay, *maxMonth, *maxYear = NULL;

                size_t *minInf = &(stralen_p[curr_hw].inf);
                if (stralen_p[curr_hw].minDate == NULL) {
                    dateStrs *minDate_p_t =
                        (dateStrs *)malloc(sizeof(dateStrs));
                    if (minDate_p_t == NULL) {
                        fprintf(stdout, MEMFAIL);
                        return 1;
                    }
                    stralen_p[curr_hw].minDate = minDate_p_t;

                    minDay = &(stralen_p[curr_hw].minDate->day);
                    minMonth = &(stralen_p[curr_hw].minDate->month);
                    minYear = &(stralen_p[curr_hw].minDate->year);

                    *minDay = *minMonth = *minYear = -1;
                }
                if (stralen_p[curr_hw].maxDate == NULL) {
                    dateStrs *maxDate_p_t =
                        (dateStrs *)malloc(sizeof(dateStrs));
                    if (maxDate_p_t == NULL) {
                        fprintf(stdout, MEMFAIL);
                        return 1;
                    }
                    stralen_p[curr_hw].maxDate = maxDate_p_t;

                    maxDay = &(stralen_p[curr_hw].maxDate->day);
                    maxMonth = &(stralen_p[curr_hw].maxDate->month);
                    maxYear = &(stralen_p[curr_hw].maxDate->year);

                    *maxDay = *maxMonth = *maxYear = -1;
                }

                size_t count_dates_str = 0;

                dateStrs *currDates_p = stralen_p[curr_hw].curr_date_str;
                while (*curr_str != '\0') {
                    if (sscanf(curr_str, "%d/%d/%d%ln", &day_c, &mounth_c,
                               &year_c, &temp_ptr) == 3) {
                        curr_str += temp_ptr;
                        if (day_c > 0 && mounth_c > 0 && year_c > 0) {
                            if (mounth_c > 12 || day_c > 31) {
                                continue;
                            }

                            if (day_c < 31) {
                                size_t check_day = 0;
                                int leap =
                                    ((year_c % 4 == 0 && year_c % 100 != 0) ||
                                     (year_c % 400)); // проверка на вис год
                                switch (mounth_c) {
                                case 4:
                                case 6:
                                case 9:
                                case 11:
                                    check_day = day_c > 30 ? 1 : 0;
                                    break;
                                case 2:
                                    size_t check_leap = leap ? 29 : 28;
                                    check_day = day_c > check_leap ? 1 : 0;
                                    break;
                                default:
                                    check_day = day_c > 31 ? 1 : 0;
                                }

                                if (check_day == 1) {
                                    continue;
                                }
                            }
                        } else {
                            continue;
                        }

                        if (count_dates_str == capacity_dates) {
                            capacity_dates *= 2;
                            dateStrs *currDates_p_t = (dateStrs *)realloc(
                                currDates_p, sizeof(dateStrs) * capacity_dates);
                            if (currDates_p_t == NULL) {
                                fprintf(stdout, MEMFAIL);
                                return 1;
                            }
                            stralen_p[curr_hw].curr_date_str = currDates_p_t;
                            currDates_p = stralen_p[curr_hw].curr_date_str;
                        }

                        if (cmp_dates(&(currDates_p[count_dates_str]),
                                      stralen_p[curr_hw].maxDate) > 0) {
                            *maxDay = day_c;
                            *maxMonth = mounth_c;
                            *maxYear = year_c;
                        }
                        if (*minDay == -1 && *minMonth == -1 &&
                            *minYear == -1) {
                            *minDay = day_c;
                            *minMonth = mounth_c;
                            *minYear = year_c;
                        } else if (cmp_dates(&(currDates_p[count_dates_str]),
                                             stralen_p[curr_hw].minDate) < 0) {
                            *minDay = day_c;
                            *minMonth = mounth_c;
                            *minYear = year_c;
                        }
                        currDates_p[count_dates_str].day = day_c;
                        currDates_p[count_dates_str].month = mounth_c;
                        currDates_p[count_dates_str].year = year_c;
                        count_dates_str++;

                        day_c = mounth_c = year_c = 0;
                    } else {
                        curr_str++;
                    }
                }

                if (count_dates_str == 0) {
                    stralen_p[curr_hw].inf = 1;
                    *minInf = 1;
                    *minDay = *minMonth = *minYear = -1;
                    stralen_p[curr_hw].date_c = 1;
                } else {
                    stralen_p[curr_hw].inf = 0;
                    if (count_dates_str < capacity_dates) {
                        dateStrs *arr_trunc_dates_p_t = (dateStrs *)realloc(
                            currDates_p, sizeof(dateStrs) * count_dates_str);
                        if (arr_trunc_dates_p_t == NULL) {
                            fprintf(stdout, MEMFAIL);
                            return 1;
                        }
                        stralen_p[curr_hw].curr_date_str = arr_trunc_dates_p_t;
                        currDates_p = arr_trunc_dates_p_t;
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
        arr_trunc(strs, curr_hw);
    }
    size_t *totallen = &(strs->total_len);
    *totallen = curr_hw;

    return 0;
}

int dupl_rows(strs_all *strs, size_t curr_hw) {
    free(strs->str_a_len[curr_hw].str);
    strs->str_a_len[curr_hw].lenstr = 0;
    char *temp_p_dupl = (char *)malloc(sizeof(char) * LENSTR_D);
    if (temp_p_dupl == NULL) {
        fprintf(stdout, MEMFAIL);
        return 1;
    }
    strs->str_a_len[curr_hw].str = temp_p_dupl;

    return 0;
}

int incr_str_len_arr(strs_all *strs, size_t curr_hw, size_t *lenstr) {
    *lenstr *= 2;
    char *temp_p_str_len =
        (char *)realloc(strs->str_a_len[curr_hw].str, sizeof(char) * *lenstr);
    if (temp_p_str_len == NULL) {
        fprintf(stdout, MEMFAIL);
        return 1;
    }
    strs->str_a_len[curr_hw].str = temp_p_str_len;

    return 0;
}

int incr_str_arr(strs_all *strs, size_t *hw, size_t curr_hw, size_t lenstr) {
    *hw *= 2;
    strsalen *temp_p_hw =
        (strsalen *)realloc(strs->str_a_len, sizeof(strsalen) * (*hw));
    if (temp_p_hw == NULL) {
        fprintf(stdout, MEMFAIL);
        return 1;
    }
    strs->str_a_len = temp_p_hw;
    strs->total_len = (*hw);

    for (size_t j = curr_hw; j < (*hw); j++) {
        char *temp_p_str = (char *)malloc(sizeof(char) * lenstr);
        if (temp_p_str == NULL) {
            fprintf(stdout, MEMFAIL);
            return 1;
        }
        strs->str_a_len[j].str = temp_p_str;
    }

    return 0;
}

int arr_trunc(strs_all *strs, size_t curr_hw) {
    strsalen *temp_p_trnc =
        (strsalen *)realloc(strs->str_a_len, sizeof(strsalen) * curr_hw);
    if (temp_p_trnc == NULL && curr_hw > 0) {
        fprintf(stdout, MEMFAIL);
        return 1;
    }
    strs->str_a_len = temp_p_trnc;

    return 0;
}

int cmp_dates(const dateStrs *ptr1, const dateStrs *ptr2) {
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