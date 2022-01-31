#include <stdio.h>

int strlenp(char *s);

int main()
{
	printf("%d\n", strlenp("array"));

	return 0;
}
/* strlen: return length of string s */
int strlenp(char *s)
{
	int n;

	for (n = 0; *s != '\0'; s++){
		n++;
	}

	return n;
}
