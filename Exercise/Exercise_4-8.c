#include <stdio.h>
#include <stdlib.h>	/* for atof() */

#define MAXOP	100	/* max size of operand or operator */
#define NUMBER	'0'	/* signal that a number was found */
#define MAXVAL  100	/* maximum depth of val stack */ 
#define COMMAND 'c'	/* ��������������ѧ���� */

int sp = 0;			/* next free stack position */
double val[MAXVAL];	/* value stack */
int getop(char []);
void push(double);
double pop(void);
void command(char []);
int comparestr(char a[], char b[]);

double recent = 0.0;		/* ����洢�������ӡֵ�ı��� */

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
			case COMMAND:
				command(s);
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
				recent = val[sp];   
				break;
			default:
				printf("error: unknown cammand %s\n", s);
				break;
		}
	}
	return 0;
}

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
	
	if (!isdigit(c) && c != '.' && c != '-' && !islower(c)){
		return c;	/* not a number */
	}
	
	i = 0;		/* ע��������Ȼ����Ϊ0��������������++i���Ǵ�1��ʼ�ģ�������Ϊ�Ѿ���ȡ��һ��ֵ�� */
	if (islower(c)){
		while (islower(s[++i] = c = getch()))
			;
		s[i] = '\0';
		if (c != EOF){
			ungetch(c);
		}
		return COMMAND; 
	}
	
	if (c == '-'){
		s[0] = c = getch();	/* ����s[0]�Ѿ���ֵ�ˣ�Ҳ����'-'��������Ҫ����һ��s[0]��ֵ����Ϊ������sign��ʵ�ָ��ţ�����ֱ�ӽ����ֵ�һλ������ */ 
		if (isdigit(c)){
			sign = -1;
		}else{
			s[1] = '\0';	/* ��Ҫע��������Ҫ�����ַ�������Ȼ���ܻᵼ��������� */ 
			ungetch(c);
			return '-';
		}
	}
	
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
char buf = 0;	/* buffer for ungetch */

/* getch���ڻ�ȡ�ַ�������ungetch����buf��������Ҫ�ٴ�ʹ�õ��ַ� */ 
int getch(void) /* get a (possibly pushed back) character */
{
	char c = 0;
	if (buf != 0){
		c = buf;
		buf = 0;
		return c;
	}else{
		getchar();
	}
}

/* 
��getop�У�����ڻ�ȡ���ֵ�ʱ������һ�������ֵ��ַ�����ô�ͱ�ʾ������ֻ�ȡ��ϣ������жϵ�ʱ�򣬾��Ѿ���ȡ����������ֵ��ַ�����ʱ�����Ҫ������뻺��buf�����У���һ��getop��ʱ�����ʹ�á�
�������˺���Ϊʲô��ֱ�Ӻ��Ե�����Ϊ�ǿո�Ҳû�á�����û�п��ǵ�1 1+����ʽ�ӵ���������ֱ�Ӻ��ԵĻ����Ӻžͻᱻ���Ե���
*/     
void ungetch(int c)	/* push character back on input */
{
	if (buf != 0){	
		printf("ungetch: too many characters\n");
	}else{
		buf = c;
	}
}

/* �����ж������������ִ�� */ 
void command(char s[])
{
	int i;			/* swap��������ȡջ��ֵ���±꣬��sp���ÿ��ǻ�ԭ�����⣬�鷳������duplicate��ʱ����sp����Ϊsp�����Ҫ+1*/ 
	double dup;		/* ���Ƶ�ջ�ж�����ֵ */ 
	double temp;	/* ��ȡ���������ջ����Ŀհ���ʱ����Ԫ�ص�ֵ */
	
	i = 0; 
	dup =0.0;
	
	if (comparestr(s, "all") == 1){	/* ��ʾջ������Ԫ�ص�ֵ */
		printf("top -> buttom value is:\n");
		while (sp > 0){
			printf("\t%.8g\n",val[--sp]);
		}
	}else if (comparestr(s, "top") == 1){	/* ��ʾջ������Ԫ�ص�ֵ */
		i = sp - 1;
		printf("top value is %.8g\n",val[i]);
	}else if (comparestr(s, "dup") == 1){	/* ����ջ������Ԫ�ص�ֵ */
		dup = val[sp - 1];
		val[sp++] = dup;
	}else if (comparestr(s, "swap") == 1){	/* ��������������Ԫ�ص�ֵ */ 
		i = sp - 1;
		dup = val[i];
		val[i] = val[i-1];
		val[i-1] = dup;
	}else if (comparestr(s, "clear") == 1){	/* ���ջ */
		temp = val[sp--];
		while (sp >= 0){
			val[sp--] = temp;
		}
	}else if (comparestr(s, "sin" ) == 1){	/* sin���� */
		push(sin(pop()));
	}else if (comparestr(s, "exp" ) == 1){	/* e��x�η����� */
		push(exp(pop()));
	}else if (comparestr(s, "pow" ) == 1){	/* x��y�η����㣨�����㣩 */
		temp = pop();
		if (isdigit(pop())){
			push(pow(pop(), temp));
		}else{
			printf("Need more number\n");
		}
	}else if (comparestr(s, "r" ) == 1){	/* ����洢�������ӡֵ�ı��� */
		printf("Recently printed value is %.8g\n", recent);
	}else{
		printf("error: unknown cammand %s\n", s);
	}
}

/* �Ա��ַ����Ƿ�һ���������ж���������� */
int comparestr(char a[], char b[])
{
	int i;
	
	for (i=0; a[i] == b[i]; i++){
		if (a[i] == '\0'){
			return 1;
		}
	}
	return 0;
}
