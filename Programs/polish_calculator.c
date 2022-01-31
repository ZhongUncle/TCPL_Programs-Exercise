#include <stdio.h>
#include <stdlib.h>	/* for atof() */

#define MAXOP	100	/* max size of operand or operator */
#define NUMBER	'0'	/* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
main()
{
	int type;
	double op2;
	char s[MAXOP];
	
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0){
					push(pop() / op2);
				}else{
					printf("error: zero divisor\n");
				}
				break;
			case '\n':
				printf("\t%.8g\n", pop()); 
				break;
			default:
				printf("error: unknown cammand %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL 100	/* maximum depth of val stack */ 

int sp = 0;			/* next free stack position */
double val[MAXVAL];	/* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL){
		val[sp++] = f;
	}else{
		printf("error: stack full, can't push %g\n", f);
	}
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0){
		return val[--sp];
	}else{
		printf("error: stack empty\n");
		return 0.0;
	}
}

#include <ctype.h> 

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;
	
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.'){
		return c;	/* not a number */
	}
	i = 0;
	if (isdigit(c)){/* collect integer part */
		while (isdigit(s[++i] = c = getch()))	/* 虽然之前让i=0了，但是这里++i会让i从1开始，因为之前s[0]已经等于c来获取了第一个数字了 */
			;
	}
	if (c == '.'){	/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	}
	s[i] = '\0';
	if (c != EOF){
		ungetch(c);
	}
	return NUMBER;
}

/* 
这里设计的非常巧妙
 
buffer可以帮助处理输入式子之间的空格
例如 1 1 +  这个这式子，在将第一个1通过getop放入栈中之后，（104-106行）ungetch会将buf[0]的值设置为'\b'，因为这时候c='\b'，bufp会变成1。
这样在下一次getop的时候getch会因为bufp=1>0，返回buf[--1]，也就是buf[0]的值，也就是'\b'，然后在（88-90行）处理完空格之后，进行下一轮获取push数字。 
 */ 
#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

/* getch用于获取字符，包括ungetch放入buf数组中需要再次使用的字符 */ 
int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* 
在getop中，如果在获取数字的时候遇到一个非数字的字符，那么就表示这个数字获取完毕，但是判断的时候，就已经获取了这个非数字的字符，这时候就需要将其放入缓存buf数组中，下一次getop的时候继续使用。
可能有人好奇为什么不直接忽略掉，认为是空格也没用。这是没有考虑到1 1+这种式子的情况，如果直接忽略的话，加号就会被忽略掉。
*/     
void ungetch(int c)	/* push character back on input */
{
	if (bufp >= BUFSIZE){
		printf("ungetch: too many characters\n");
	}else{
		buf[bufp++] = c;
	}
}
