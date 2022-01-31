//
//  main.c
//  binsearch
//
//  Created by 钟宜江 on 2021/8/29.
//

#include <stdio.h>

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
// 是最高位的编号，也就是数组数量-1
int binsearch(int x, int v[], int n) {
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return  mid;;
    }
    return -1;  /* no match */
}

int main() {
    int arr[] = {1,2,3,4,12,31,15};
    printf("%d\n",binsearch(31, arr, 6));
    return 0;
}
