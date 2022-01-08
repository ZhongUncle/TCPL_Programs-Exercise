#include <stdio.h>

char mstrncpy(char *s, char *ct, int n);
//char mstrncat(char *s, char *ct, int n);
int mstrncmp(char *cs, char *ct, int n);

int main()
{
	char str1[] = "";
	char str2[] = "The quick brown fox jumped over the lazy dog.";
	char str3[] = "abc";
	char str4[] = "def";
    char str5[] = "";
    char str6[] = "The quick brown fox jumped over the lazy dog.";
    
    mstrncpy(str1, str2, 10);
    printf("%s\n", str1);       /* This print 'The quick ' is right. */
//    mstrncat(str3, str4, 3);
//    printf("%s\n", str3);
//    printf("%s\n", str1);       /* Why there print 'ef' is wrong, when mstrncat active? */
    int ret = mstrncmp(str5, str6, 3);

    if(ret < 0) {
       printf("str1 is less than str2\n");
    } else if(ret > 0) {
       printf("str1 is more than str2\n");
    } else {
       printf("str1 is equal to str2\n");
    }

	return 0;
}

char mstrncpy(char *s, char *ct, int n)
{
	int i = 0;

	while (*ct != '\0' && i <= (n - 1)){
		*s++ = *ct++;
		i++;
	}
	*s = '\0';
	return *s;
}

/* When this function appear, the first function, mstrncpy, have something wrong */
//char mstrncat(char *s, char *ct, int n)
//{
//	int i = 0;
//	while (*s != '\0'){
//		s++;
//	}
//
//	while (*ct != '\0' && i <= (n - 1)){
//		*s++ = *ct++;
//		i++;
//	}
//	*s = '\0';
//	return *s;
//}

int mstrncmp(char *cs, char *ct, int n)
{
    int i = 0;
    int r = 0;
    
    if (*cs == '\0' && *ct != '\0'){
        return -*ct;
    }else if (*cs != '\0' && *ct == '\0'){
        return *cs;
    }else if (*cs == '\0' && *ct == '\0'){
        return 0;
    }
    
    while (i <= n-1 && *cs != '\0' && *ct != '\0'){
        r += (*cs++ - *ct++);
        i++;
    }
    return r;
}

