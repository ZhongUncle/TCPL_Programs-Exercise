#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void reverse(char s[]);
void itob(int n, char s[], int b);

int main()
{
	int num, base;
	char s[MAXLINE];
	
	num=-300;
	base=16;
	
	itob(num,s,base);
	
	printf("%s\n",s);
	return 0;
} 

void itob(int n, char s[], int b)
{
	int i, c, sign;
	
	if ((sign=n)<0){
		n=-n;
	}
	
	i=0;
	
	do{
		c=n%b;
		s[i++]=(c<=9)?c+'0':c-10+'a';
		n = (n-c)/b;//比直接除以b精度更高，不用四舍五入 
	}while(n>=b);
	s[i++]=n+'0';
	if (sign<0){
		s[i++]='-';
	}
	s[i]='\0';
	reverse(s);
} 

void reverse(char s[])
{
	int i,j,c;
	
	for (i=0,j=strlen(s)-1;i<j;i++,j--){
		c=s[j];s[j]=s[i];s[i]=c;
	}
}





