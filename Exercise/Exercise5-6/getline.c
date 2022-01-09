#include <stdio.h>

/* specicalized version */
#define MAXLINE 1000

/* this must be array, instead of pointer. Because there need space to store values, pointer can't do it. */
char line[MAXLINE];    /* current input line */

int mgetline(char *s, int max);

int main()
{
    mgetline(line, MAXLINE);
    printf("%s\n", line);
    
    return 0;
}

/* getline: specialized version */
int mgetline(char *s, int max) {
    char c;
    int i = 1;
    /* There can't use pointer directly, because pointer point a variable(store its value), instead of store a value directly. getchar() is dynamic, it's not a stored value. */
    while ((c = getchar()) != '\n' && i <= max){
        *s++ = c;
        i++;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return 0;
}
