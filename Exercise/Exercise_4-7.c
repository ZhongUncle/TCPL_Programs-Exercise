#include <stdio.h>

#define MAXVAL 100

int getch(void);
void ungetch(int c);
void ungets(char s[]);

main()
{
	int i, c;
	char s[MAXVAL];
	
	while ((c = getch()) != EOF){
		i=0;
		s[i] = c; 
		while ((s[++i] = c = getch()) != EOF && c != '\n'){
			;
		}
		
		s[i] = '\0';
		
		if (c != EOF){
			ungets(s);
		}
		
		printf("%s\n", s);
	}
	
}

#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

/* getch用于获取字符，包括ungetch放入buf数组中需要再次使用的字符 */ 
int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}   
void ungetch(int c)	/* push character back on input */
{
	if (bufp >= BUFSIZE){
		printf("ungetch: too many characters\n");
	}else{
		buf[bufp++] = c;
	}
}

/* 返回输入的整个字符串 */
void ungets(char s[])
{
	int i;
	
	i = strlen(s);
	
	while (i > 0){		/* 这里i要大于等于1，不然会重新获取'\0'，会出错 */
		ungetch(s[--i]);
	}	
}
