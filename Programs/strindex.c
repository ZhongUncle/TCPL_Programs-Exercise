#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[]="ould";
//"Ah Love! could you and I with Fate conspire\nTo grasp this sorry Scheme ofThing entire,\nWould not we shatter it to bits -- and then\nre-mould it nearer to the Heart's Desire!"

/* find all lines matching pattern */
main()
{
	char line[MAXLINE];
	int found = 0;
	
	while (getline(line, MAXLINE) > 0) {
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	}
	
	return found;
}

/* getline: get line into s, return length */
int getline(char s[], int lim)
{
	int c, i;
	
	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n'){
		s[i++] = c;
	}
	if (c == '\n'){
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}

/* strindex: return index of t in s, -1 if none */
int strindex(char s[], char t[])
{
	int i, j, k;
	
	for (i = 0; s[i] != '\0'; i++){
		//这里将j=i是保持i的值不变，方便后面返回。不用像我的版本一样复杂地将值传递给r，让r保持获取到index值
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++,k++)
			;
		//这里是在遇到字符串的最后一位'\0'的时候，将值返回 
		if (k > 0 && t[k] == '\0'){
			return i;
		}
	}
	return -1;
}
//我自己的版本 
//#include <stdio.h>

//int main()
//{
//	int i, j, r;
//	char a[]="aababcaaa";
//	char b[]="abc";
//	
//	for (i=0; a[i]!='\0'; i++){
//		r=0;
//		j=0;
//		if (a[i]==b[j]){
//			r=i;
//		}
//		while (a[i]==b[j] && b[j]!='\0'){
//			j++;
//			i++;
//		}
//		if (b[j]=='\0'){
//			return r;
//		}
//	}
//	return -1;
//} 

