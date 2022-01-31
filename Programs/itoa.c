#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void reverse(char s[]);
void itoa(int n, char s[], int w);

int main()
{
	int num, wid;
	char s[MAXLINE];
	
	num=300;
	wid=10;
	
	itoa(num,s,wid);
	
	printf("%s\n",s);
	return 0;
} 

void itoa(int n, char s[], int w)
{
	int i, c, sign;
	int l;
	
	if ((sign=n)<0){
		n=-n;
	}
	
	i=0;
	
	do{
		c=n%10;
		s[i++]=c+'0';
		n = (n-c)/10;//比直接除以b精度更高，不用四舍五入 
	}while(n>=10);
	s[i++]=n+'0';
	if (sign<0){
		s[i++]='-';
	}
	if (i<=w-1){//-1是因为w是数量，总数比i大1 
		l=w-(i+1);//需要添加的空格数，+1是因为i从0开始的 
		while(l>0){
			s[i++]=' ';
			l--;
		}
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
