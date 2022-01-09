#include <stdio.h>
#include <string.h>

void mitoa(int n, char *str);
void reverse(char *);

int main()
{
    int a = 12;
    char str[100];
    mitoa(a, str);
    reverse(str);   /* reverse(char *) need written in here, or not in mitoa(), that will not work */
    printf("%s\n", str);
    
    return 0;
}

void mitoa(int n, char *str)
{
    int sign = 1;

    if (n < 0){
        sign = -1;
        n = -n;
    }
    while (n > 0){
        *str = n%10 + '0';
        n = n / 10;
        str++;
    }
    
    if (sign == -1){
        *str++ = '-';
    }
    *str = '\0';
}


void reverse(char *s)
{
    char *n;
    int temp;
    
    for (n = s+(strlen(s)-1); s < n; s++, n--){
        temp = *s; *s = *n; *n = temp;
    }
}
