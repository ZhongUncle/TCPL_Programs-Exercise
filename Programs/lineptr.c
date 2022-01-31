#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */ 

char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
    int nlines;     /* number of input lines read */
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    }else{
        printf("error: input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 100      /* max length of any input line */
int mgetline(char *, int);
char *alloc(int);

/* readline: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    
    nlines = 0;
    while ((len = mgetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL){
            return -1;
        }else{
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    
    for (i = 0; i < nlines; i++){
        printf("%s\n", lineptr[i]);
    }
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

#define ALLOCSIZE 10000    /* size of available space */

static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;        /* next free position */

char *alloc(int n)    /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n){    /* it fits */
        allocp += n;
        return allocp - n;    /* old p */
    }else{    /* not enough room */
        return 0;
    }
}
