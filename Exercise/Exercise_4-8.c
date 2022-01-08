#include <stdio.h>
#include <stdlib.h>	/* for atof() */

#define MAXOP	100	/* max size of operand or operator */
#define NUMBER	'0'	/* signal that a number was found */
#define MAXVAL  100	/* maximum depth of val stack */ 
#define COMMAND 'c'	/* 输入的命令或者数学命令 */

int sp = 0;			/* next free stack position */
double val[MAXVAL];	/* value stack */
int getop(char []);
void push(double);
double pop(void);
void command(char []);
int comparestr(char a[], char b[]);

double recent = 0.0;		/* 输出存储最近被打印值的变量 */

int sign = 1;		/* 来处理输入的负数 */

/* reverse Polish calculator */
main()
{
	int type;
	double op2;
	char s[MAXOP];
	int m1, m2;		/* 模计算的时候要将double转换为int类型，不然会编译失败 */
	
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
	
	i = 0;		/* 注意这里虽然设置为0，但是下面由于++i，是从1开始的，这是因为已经获取了一个值了 */
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
		s[0] = c = getch();	/* 由于s[0]已经有值了，也就是'-'，这里需要更改一下s[0]的值，因为是利用sign来实现负号，所以直接将数字第一位给它， */ 
		if (isdigit(c)){
			sign = -1;
		}else{
			s[1] = '\0';	/* 需要注意这里需要结束字符串，不然可能会导致数组溢出 */ 
			ungetch(c);
			return '-';
		}
	}
	
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
char buf = 0;	/* buffer for ungetch */

/* getch用于获取字符，包括ungetch放入buf数组中需要再次使用的字符 */ 
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
在getop中，如果在获取数字的时候遇到一个非数字的字符，那么就表示这个数字获取完毕，但是判断的时候，就已经获取了这个非数字的字符，这时候就需要将其放入缓存buf数组中，下一次getop的时候继续使用。
可能有人好奇为什么不直接忽略掉，认为是空格也没用。这是没有考虑到1 1+这种式子的情况，如果直接忽略的话，加号就会被忽略掉。
*/     
void ungetch(int c)	/* push character back on input */
{
	if (buf != 0){	
		printf("ungetch: too many characters\n");
	}else{
		buf = c;
	}
}

/* 用于判断输入命令，并且执行 */ 
void command(char s[])
{
	int i;			/* swap中用来获取栈中值的下标，用sp还得考虑还原的问题，麻烦，但是duplicate的时候用sp是因为sp最后需要+1*/ 
	double dup;		/* 复制的栈中顶部的值 */ 
	double temp;	/* 获取的用于清除栈数组的空白临时数组元素的值 */
	
	i = 0; 
	dup =0.0;
	
	if (comparestr(s, "all") == 1){	/* 显示栈中所有元素的值 */
		printf("top -> buttom value is:\n");
		while (sp > 0){
			printf("\t%.8g\n",val[--sp]);
		}
	}else if (comparestr(s, "top") == 1){	/* 显示栈顶部的元素的值 */
		i = sp - 1;
		printf("top value is %.8g\n",val[i]);
	}else if (comparestr(s, "dup") == 1){	/* 复制栈顶部的元素的值 */
		dup = val[sp - 1];
		val[sp++] = dup;
	}else if (comparestr(s, "swap") == 1){	/* 交换顶部的两个元素的值 */ 
		i = sp - 1;
		dup = val[i];
		val[i] = val[i-1];
		val[i-1] = dup;
	}else if (comparestr(s, "clear") == 1){	/* 清空栈 */
		temp = val[sp--];
		while (sp >= 0){
			val[sp--] = temp;
		}
	}else if (comparestr(s, "sin" ) == 1){	/* sin计算 */
		push(sin(pop()));
	}else if (comparestr(s, "exp" ) == 1){	/* e的x次方计算 */
		push(exp(pop()));
	}else if (comparestr(s, "pow" ) == 1){	/* x的y次方计算（幂运算） */
		temp = pop();
		if (isdigit(pop())){
			push(pow(pop(), temp));
		}else{
			printf("Need more number\n");
		}
	}else if (comparestr(s, "r" ) == 1){	/* 输出存储最近被打印值的变量 */
		printf("Recently printed value is %.8g\n", recent);
	}else{
		printf("error: unknown cammand %s\n", s);
	}
}

/* 对比字符串是否一样，用于判断输入的命令 */
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
