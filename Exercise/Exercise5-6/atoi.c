#include <stdio.h>
#include <ctype.h>

int matoi(char *s);

int main()
{
    char s[] = "123";
    int p;
    
    p = matoi(s);
    
    printf("%d\n", p);
    
    return 0;
}

/* atoi: convert s to integer */
int matoi(char *s)
{
    int n = 0;
    int sign = 1;
    
    while (isspace(*s)){
        s++;
    }
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-'){
        s++;
    }
    while (isdigit(*s)){
        n = 10 * n + (*s - '0');
        s++;
    }
    return sign * n;
}
