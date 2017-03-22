/***********************************************************************
 *  > File Name: main.c
 *  > Author: zhushuhuang
 *  > Mail: zsh5318@gmail.com
 *  > Created Time: Sun 14 Sep 2014 09:19:34 AM CST
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_week(int, int, int);
void print_month_of_calender(int, int);
int main(int x, char **date) {
    int year = 0, month = 0, day = 0, week;
    int d, i, dmonth;
    int a[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int b[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char WEEK[10];
    if (x == 1) {
        printf("\nERROR! You forgot to enter the date you want to view\n");
        exit(0);
    }

    // get input date
    i = 0, d = -1;
    while (date[1][i]) {
        if ((date[1][i] == '/' || date[1][i] == '.' || date[1][i] == '-') && d == -1) {
            d = 0; i++; continue;
        }
        if ((date[1][i] == '/' || date[1][i] == '.' || date[1][i] == '-') && d == 0) {
            d = 1; i++; continue;
        }
        if (d == -1) {
            year = year * 10 + (date[1][i] - '0');
        }
        if (d == 0) {
            month = month * 10 + (date[1][i] - '0');
        }
        if (d == 1) {
            day = day * 10 + (date[1][i] - '0');
        }
        i++;
    }

    week = calculate_week(year, month, day);
    if (day > 0 && month > 0) {
        switch (week) {
            case 0: strncpy(WEEK, "SUNDAY", sizeof(WEEK)); break;
            case 1: strncpy(WEEK, "MONDAY", sizeof(WEEK)); break;
            case 2: strncpy(WEEK, "TUESDAY", sizeof(WEEK)); break;
            case 3: strncpy(WEEK, "WEDNESDAY", sizeof(WEEK)); break;
            case 4: strncpy(WEEK, "THURSDAY", sizeof(WEEK)); break;
            case 5: strncpy(WEEK, "FRIDAY", sizeof(WEEK)); break;
            case 6: strncpy(WEEK, "SATURDAY", sizeof(WEEK)); break;
        }
        printf("\nThis day is %s \(%d)\n", WEEK, week);
    }

    // select output
    if (month > 0) {
        if (day > 0) {
            week = calculate_week(year, month, 0);
        }
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            dmonth = b[month];
        } else {
            dmonth = a[month];
        }
        printf("\nThe calender of %d-%d\n", year, month);
        print_month_of_calender(week, dmonth);
        printf("\n");
    } else {
        for (month = 1; month <= 12; ++month) {
            printf("\nThe calender of %d-%d\n", year, month);
            week = calculate_week(year, month, day);
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                dmonth = b[month];
            } else {
                dmonth = a[month];
            }
            print_month_of_calender(week, dmonth);
        }
    }
    return 0;
}
void print_month_of_calender(int week, int dmonth) {
    int i;
    week = (week + 1) % 7;
    printf("****************************\n");
    printf("SUN MON TUE WEN THU FRI SAT\n");
    for (i = 0; i < week; i++) {
        printf("    ");
    }
    for (i = 1; i <= dmonth; i++) {
        printf("%2d  ", i);
        week++;
        if (week % 7 == 0 && i != dmonth)
            printf("\n");
    }
    printf("\n****************************\n");
}
int calculate_week(int year, int month, int day) {
    int week, d, dy, dm, m2;
    if (year == 2000) {     // calculate the number of leap year
        d = 0;
    } else if (year > 2000) {
        d = (year - 1 - 2000) / 4 - (year - 1 - 2000) / 100 + (year - 1 - 2000) / 400 + 1;
    } else {
        d = (year - 2000) / 4 - (year - 2000) / 100 + (year - 2000) / 400;
    }
    dy = (year - 2000) + d;
    if ((year%4 == 0 && year%100 != 0) || (year % 400 == 0)) {
        m2 = 1;
    } else {
        m2 = 0;
    }
    switch (month) {    // calculate the days after mod 7
        case 1: dm = 0; break;
        case 2: dm = 3; break;
        case 3: dm = 3 + m2; break;
        case 4: dm = 6 + m2; break;
        case 5: dm = 1 + m2; break;
        case 6: dm = 4 + m2; break;
        case 7: dm = 6 + m2; break;
        case 8: dm = 2 + m2; break;
        case 9: dm = 5 + m2; break;
        case 10: dm = m2; break;
        case 11: dm = 3 + m2; break;
        case 12: dm = 5 + m2; break;
    }

    week = (dy + dm + day - 1 + 6) % 7;
    if (week < 0)
        week += 7;
    return week;
}
