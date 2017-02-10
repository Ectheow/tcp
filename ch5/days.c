#include <stdio.h>
static char leaps[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static char noleaps[13] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
static char *daytab[] = {
    leaps,
    noleaps
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if (year < 0) {
        printf("Error: year < 0: %d\n", year);
        return -1;
    } 

    if (month > 12 || month <= 0) {
        printf("Error: invalid month %d\n", month);
        return -1;
    }

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    if (day <= 0 || day > daytab[leap][month]) {
        printf("Error: not that many days in month %d (days %d)\n",
                month,
                day);
        return -1;
    }

    for(i = 1; i< month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    if (year < 0) {
        printf("Error: invalid year: %d\n",
                year);
        return;
    }
    if (yearday < 0 || yearday > 365) {
        printf("Error: yearday not valid: %d\n",
                yearday);
        return;
    }

    leap = year%4 == 0 && year%100 != 0 || year % 400 == 0;
    for (i=1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;
}

int main()
{
    int mo, day;

    month_day(1988, 53, &mo, &day);
    printf("month and day for 53rd day of 1988: %d %d\n", 
            mo, 
            day);
    printf("day of year for the 3rd of august 1989: %d\n",
            day_of_year(1988, 8, 3));

    printf("Errors: \n");
    printf("bad yearday and bad year\n");
    month_day(2012, 500, &mo, &day);
    month_day(-1, 500, &mo, &day);
    printf("bad month and bad day\n");
    day_of_year(2012, 13, 31);
    day_of_year(2000, 1, 32);

}
