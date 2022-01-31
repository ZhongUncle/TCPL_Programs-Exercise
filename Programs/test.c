#include <stdio.h>

#define MAXVAL 100

int comparestr(char a[], char b[]);

main()
{
	 char a[MAXVAL]="swap";
	 char b[MAXVAL]="swapaw";
	 
	 int issame = 0;
	 
	 issame = comparestr(a, "swap");
	 
	 if (issame == 1){
	 	printf("it is same command\n");
	 }else{
	 	printf("it isn't same command\n");
	 }
	 
} 

int comparestr(char a[], char b[]){
	int i;
	
	for (i=0; a[i] == b[i]; i++){
		if (a[i] == '\0'){
			return 1;
		}
	}
	return 0;
}
