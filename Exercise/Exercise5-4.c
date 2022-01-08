#include <stdio.h>

int mstrend(char *s, char *t);

int main()
{
	char s[] = "abcddd";
	int r;
	r = mstrend(s, "bc");
	printf("%d\n", r);
	return 0;
}

int mstrend(char *s, char *t)
{
    char *a = t;
	while (*s != '\0'){
		if (*s == *t){
			while (*s == *t && *s != '\0' && *t != '\0'){
				s++;
				t++;
			}
			if (*s == '\0' && *t == '\0'){
				return 1;
            }else{
                t = a;
            }
		}else{
			s++;
		}
	}
	return 0;
}
