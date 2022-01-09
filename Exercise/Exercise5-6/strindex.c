#include <stdio.h>

int strindex(char *s, char *t);

int main()
{
    int i;
    char str[] = "abdsdfabcd";
    char cmp[] = "abc";
    i = strindex(str, cmp);

    printf("%d\n", i);

    return 0;
}

int strindex(char *s, char *t)
{
    int i;

    for (i = 0; *s != '\0'; s++, i++){
        while (*t != '\0' && *s == *t){
            s++;
            t++;
        }
        if (*t == '\0' && i > 0){
            return i;
        }
    }
    return -1;
}
