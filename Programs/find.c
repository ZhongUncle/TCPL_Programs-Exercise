#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int mgetline(char *line, int max);

int main(int argc, const char * argv[]) {
    char line[MAXLINE];
    // 行编号
    long lineno = 0;
    int c, except = 0,number = 0, found = 0;
    
    // 判断输入的选项（包括分隔连续输入的参数）
    while (--argc > 0 && (*++argv)[0] == '-'){
        while ((c = *++argv[0])) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n",c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    
    if (argc != 1) {
        printf("Usage: find pattern\n");
    } else {
        while (mgetline(line, MAXLINE) > 0){
            lineno++;
            if (strstr(line, argv[1]) != NULL) {
                if (number){
                    printf("%ld:",lineno);
                }
                printf("%s",line);
                found++;
            }
        }
    }
        
    return found;
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

