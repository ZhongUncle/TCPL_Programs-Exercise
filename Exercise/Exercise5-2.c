#include <stdio.h>
#include <ctype.h>

#define MAXVAL 100

int getch(void);
void ungetch(int);
int sgetint(double *pn);

int main(){
	double a[MAXVAL];
	int i = 0;
	int c = 0;

	char t;

	while ((t = sgetint(&a[i])) != '\n'){
		if (t == '-' || t == '+'){
			;
		}else{
			i++;
		}
	}	
		
	while (c <= i){
		printf("%f\n", a[c++]);
	}

	return 0;
}

/* sgetint: get next integer from input into *pn */
int sgetint(double *pn)
{
	int c, d, sign, val;

	while (isspace(c = getch())){	/* skip white space */
		;
	}
	if (!isdigit(c) && c != '\n' && c != '+' && c != '-' && c != '.'){
		ungetch(c);	/* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	
	d = c;

	if (c == '+' || c == '-'){
		c = getch();
	}

	if (c == ' '){
                ungetch(d);
                return d;
        }

	for (*pn = 0; isdigit(c); c = getch()){
		*pn = 10 * *pn + (c - '0');
	}

	if (c == '.'){
		val = 1;
	}
	while (isdigit(c = getch())){
       	        *pn = 10 * *pn + (c - '0');
		val *= 10;
        }
	
	*pn = sign * (*pn) / val;
	
	if (c != EOF){
		ungetch(c);
	}
	return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

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
