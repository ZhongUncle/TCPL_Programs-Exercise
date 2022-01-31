//
//  main.c
//  bitcount
//
//  Created by 钟宜江 on 2021/8/27.
//

#include <stdio.h>

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
    int b;
    
    for (b = 0; x!= 0; x >>= 1){
        x &= (x-1);
        b++;
    }
    return b;
}

int main() {
    printf("%d \n", bitcount(13));
    return 0;
}
