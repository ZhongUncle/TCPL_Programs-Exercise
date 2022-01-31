//
//  main.c
//  Fahrenheit-Celsius
//
//  Created by 钟宜江 on 2021/7/7.
//


///* Version 1 */
//#include <stdio.h>
//
///* print Fahrenheit-Celsius table for fahr = 0, 20 ,..., 300 */
//main() {
//
//    /* C中，所有的变量必须在所有的可执行声明之前，也就是函数的开头声明 */
//    /* 类型名称int表示整数，后面的就是变量列表 */
//    int fahr, celsius;
//    int lower, upper, step;
//
//    lower = 0;              /* lower limit of temperature table */
//    upper = 300;            /* upper limit */
//    step = 20;              /* step size */
//    fahr = lower;
//
//    /* 如果while只有一个声明，可以不用大括号 */
//    while (fahr <= upper) {
//        /* 之所以先乘再除9，而不是直接成5/9，是因为包括C在内的很多语言都会舍去小数部分，这里的5/9会变成0，这样所有的结果就都是0了 */
//        celsius = 5 * (fahr - 32) / 9;
//        /* printf的第一个参数是字符串，%指明要用第二个（或者第三个，第四个...）参数替代和参数属性，%d表示整数参数 */
//        /* 顺道一说，printf不是c语言的一部分，是标准库中的一个功能。printf的行为是被ANSI标准定义的。所以当使用使用符合ANIS标准的编译器和库的时候，标准库的内容是相同的 */
//        printf("%d\t%d\n",fahr, celsius);
//        /* 下面这个代码可以左对齐，因为我们将第一个参数定义成3位宽，第二个定义成6位宽*/
////        printf("%3d%6d\n",fahr, celsius);
//        fahr = fahr + step;
//    }
//}

///* Version 2 */
//#include <stdio.h>
//
//main() {
//
//    float fahr, celsius;
//    int lower, upper, step;
//
//    lower = 0;              /* lower limit of temperature table */
//    upper = 300;            /* upper limit */
//    step = 20;              /* step size */
//    fahr = lower;
//
//    printf("Fah\tCel\n");
//    while (fahr <= upper) {
//        celsius = (5.0/9.0) * (fahr-32.0);
//        /* 这里的%6.1f表示至少六位字符宽，和两位小数部分 */
//        printf("%3.0f%6.1f\n",fahr, celsius);
//        fahr = fahr + step;
//    }
//}

///* Version 3 */
//#include <stdio.h>
//
//main() {
//    int fahr;
//
//    for (fahr = 0; fahr <= 300; fahr = fahr + 20)
//        printf("%3d %6.1f\n",fahr, (5.0/9.0)*(fahr-32));
//}

/* Version 4 */
#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

main() {
    int fahr;
    
    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n",fahr, (5.0/9.0)*(fahr-32));
}
