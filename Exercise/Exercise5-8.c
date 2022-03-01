#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    int dayOfYear;
    int pmonth, pday;
    
    dayOfYear = day_of_year(2000, 3, 18);
    
    if (dayOfYear == -1) {
        printf("Input month error.\n");
    }else if (dayOfYear == -2){
        printf("Input day error.\n");
    }else{
        printf("3/18/2000 is %d day of year.\n", dayOfYear);
    }
    
    if (month_day(2000, 400, &pmonth, &pday) == 1){
        printf("Month is %d, day is %d.\n", pmonth, pday);
    }else{
        printf("The year day is worry!\n");
    }
    
    
    return 0;
}

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    if (month < 1 || month > 12){
        return -1;
    }else if (day < 0 || day > daytab[leap][month]){
        return -2;
    }
    
    for (i = 1; i < month; i++){
        day += daytab[leap][i];
    }
    return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    if (yearday < 0 || (leap == 0 && yearday > 365) || (leap == 1 && yearday > 366)){
        return 0;
    }
    
    for (i = 1; yearday > daytab[leap][i]; i++){
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
    return 1;
}
