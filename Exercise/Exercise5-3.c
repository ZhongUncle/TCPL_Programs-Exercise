#include <stdio.h>

void mstrcat(char *s, char *t);

int main(){
	char a[] = "abc";
	char b[] = "def";
	
	mstrcat(a, b);
	printf("%s\n", a);	

	return 0;
}

void mstrcat(char *s, char *t)
{
	int i = 0;
	while (*s != '\0'){
		s++;
	}
	while ((*s++ = *t++) != '\0'){	
		;
	}
}
