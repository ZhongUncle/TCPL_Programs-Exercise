//
//  main.c
//  Copy_Input_to_Output
//
//  Created by 钟宜江 on 2021/7/8.
//

#include <stdio.h>

///* copy input to output; 1st version */
//main() {
//    int c;
//
//    c = getchar();
//    while (c != EOF) {
//        putchar(c);
//        c = getchar();
//    }
//}

/* copy input to output; 2nd version */
main() {
    int c;

    while ((c = getchar()) != EOF)
        putchar(c);
}

