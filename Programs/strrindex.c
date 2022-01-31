#include <stdio.h>
#define MAXLINE 100

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[]="ould";
//"Ah Love! could you and I with Fate conspire\nTo grasp this sorry Scheme ofThing entire,\nWould not we shatter it to bits -- and then\nre-mould it nearer to the Heart's Desire!"

/* find all lines matching pattern */
int main()
{
	char input[MAXLINE]="aaaaabcsssaaabcdaabc";
	char test[MAXLINE]="abc";
	int rightmost = 0;
	
	rightmost=strrindex(input, test);
	
	printf("%d\n",rightmost);

	return rightmost;
}

/* strrindex: return rightmost index of t in s, -1 if none */
int strrindex(char s[], char t[])
{
	int i, j, k, r;
	
	for (i = 0; s[i] != '\0'; i++){
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++,k++)
			;
		if (k > 0 && t[k] == '\0'){
			return i;
			break;
		}
	}
	return -1;
}


 
