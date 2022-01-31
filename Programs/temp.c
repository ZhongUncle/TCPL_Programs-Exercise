#include <stdio.h>

int main() {
    int i, x;
    
    for (i=0,x=0; i<10; i++) {
        printf("%d", ++x);
    }
}
