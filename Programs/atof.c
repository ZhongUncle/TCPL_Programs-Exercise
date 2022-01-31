//#include <ctype.h>

//double atof(char s[]);

//main(){
//	double d;
//	
//}

///* atof: convert string s to double */
//double atof(char s[])
//{
//	double val, power;
//	int i, sign;
//	
//	for (i=0; isspace(s[i]); i++) /* skip white space */
//		;
//	sign = (s[i] == '-') ? -1 : 1;
//	
//	if (s[i]=='+'|| s[i]=='-'){
//		i++;
//	}
//	
//	for (val = 0.0;isdigit(a[i])){
//		val=10.0*val+(s[i]-'0');
//	}
//	
//	if (s[i]=='.'){
//		i++;
//	}
//	
//	for (power=1.0; isdigit(s[i]);i++) {
//		val = 10.0*val+(s[i]-'0');
//		power *= 10.0;
//	}
//	
//	return sign*val/power;
//}

/* 可以处理指数的版本 */
#include<stdio.h>

#define MAXLINE 1000

double itof(char s[]);

int main(){
	double a;
	char s[MAXLINE]="0e0";
	a=itof(s);
	
	printf("%f",a);
	
	return 0;
} 

double itof(char s[])
{
	double val, power;
	int i, sign, j ,esign;
	
	
	
	//忽略空格 
	for (i=0; isspace(s[i]) ;i++)
		;
		
	//处理带符号的情况 
	sign=(s[i]=='-') ? -1 : 1;
	if (s[i]=='-'||s[i]=='+'){
		i++;
	}
	
	//处理小数点和指数符号之前的部分 
	for (val=0.0; s[i]!='\0'&&s[i]!='.'&&s[i]!='e'&&s[i]!='E'; i++){
		val=val*10+s[i]-'0';
		
	}
	//处理小数点
	if (s[i]=='.'){
		i++;
		//处理小数点之后的部分
		for (power=1.0; s[i]!='\0'&&s[i]!='e'&&s[i]!='E'; power*=10, i++){
			val=val*10.0+s[i]-'0';
		}
	}
	
	//遇到指数部分 
	if (s[i]=='e'||s[i]=='E'){
		i++; 
		
		esign=(s[i]=='-') ? -1 : 1;
		if (s[i]=='-'||s[i]=='+'){
			i++;
		}else if (s[i]=='0'){
			if (val==0){
				printf("There is problem\n");
			}else{
				return 1;
			}
		} 
		
		for (j=0;s[i]!='\0';i++){
			j=j*10+s[i]-'0';
		}
		
		if (esign==-1){
			while (j>=1){
				//因为最后返回值是除，所以这里要反着写 
				power*=10;
				j--;
			}
		}else{
			while (j>=1){
				//因为最后返回值是除，所以这里要反着写 
				power/=10;
				j--;
			}
		}
	}
	
	//处理返回值 
	return (double) sign*val/power;
}

