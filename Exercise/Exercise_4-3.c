#include <stdio.h>
#include <stdlib.h>	/* for atof() */

#define MAXOP	100	/* max size of operand or operator */
#define NUMBER	'0'	/* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

int sign = 1;		/* ����������ĸ��� */

/* reverse Polish calculator */
main()
{
	int type;
	double op2;
	char s[MAXOP];
	int m1, m2;		/* ģ�����ʱ��Ҫ��doubleת��Ϊint���ͣ���Ȼ�����ʧ�� */
	
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(sign*atof(s));
				sign = 1;
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
			case '%':
				m2=pop();
				m1=pop();
				push(m1 % m2);
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
	 
	if (!isdigit(c) && c != '.' && c != '-'){
		return c;	/* not a number */
	}
	
	if (c == '-'){
		s[0] = c = getch();/* ����s[0]�Ѿ���ֵ�ˣ�Ҳ����'-'��������Ҫ����һ��s[0]��ֵ����Ȼ����Ի�ȡ��������ߵ�һλ */ 
		if (isdigit(c)){
			sign = -1;
		}else{
			s[1] = '\0';	/* ��Ҫע��������Ҫ�����ַ�������Ȼ���ܻᵼ��������� */ 
			ungetch(c);
			return '-';
		}
	}
	
	i = 0;		/* ע��������Ȼ����Ϊ1��������������++i���Ǵ�1��ʼ�ģ�������Ϊ�Ѿ���ȡ��һ��ֵ�� */
	if (isdigit(c)){/* collect integer part */
		while (isdigit(s[++i] = c = getch()))	/* ��Ȼ֮ǰ��i=0�ˣ���������++i����i��1��ʼ����Ϊ֮ǰs[0]�Ѿ�����c����ȡ�˵�һ�������� */
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
������Ƶķǳ�����
 
buffer���԰�����������ʽ��֮��Ŀո�
���� 1 1 +  �����ʽ�ӣ��ڽ���һ��1ͨ��getop����ջ��֮�󣬣�104-106�У�ungetch�Ὣbuf[0]��ֵ����Ϊ'\b'����Ϊ��ʱ��c='\b'��bufp����1��
��������һ��getop��ʱ��getch����Ϊbufp=1>0������buf[--1]��Ҳ����buf[0]��ֵ��Ҳ����'\b'��Ȼ���ڣ�88-90�У�������ո�֮�󣬽�����һ�ֻ�ȡpush���֡� 
 */ 
#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

/* getch���ڻ�ȡ�ַ�������ungetch����buf��������Ҫ�ٴ�ʹ�õ��ַ� */ 
int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* 
��getop�У�����ڻ�ȡ���ֵ�ʱ������һ�������ֵ��ַ�����ô�ͱ�ʾ������ֻ�ȡ��ϣ������жϵ�ʱ�򣬾��Ѿ���ȡ����������ֵ��ַ�����ʱ�����Ҫ������뻺��buf�����У���һ��getop��ʱ�����ʹ�á�
�������˺���Ϊʲô��ֱ�Ӻ��Ե�����Ϊ�ǿո�Ҳû�á�����û�п��ǵ�1 1+����ʽ�ӵ���������ֱ�Ӻ��ԵĻ����Ӻžͻᱻ���Ե���
*/     
void ungetch(int c)	/* push character back on input */
{
	if (bufp >= BUFSIZE){
		printf("ungetch: too many characters\n");
	}else{
		buf[bufp++] = c;
	}
}
