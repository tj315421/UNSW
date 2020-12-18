// COMP1511 Week 4 test: Print The Middle Integer of 3 Integers
//
// This program was written by Leon) WANG LIAO z5306312
// on 09/10/2020
#include<stdio.h>
int main(void) {
    int a, b, c;
    
    printf("Enter integer: ");
    scanf("%d", &a);
    printf("Enter integer: ");
    scanf("%d", &b);
    printf("Enter integer: ");
    scanf("%d", &c);
    
    if (((a >= b) && (a <= c)) || ((a >= c) && (a <= b))) {
        printf("Middle: %d\n", a);
    } else if (((b >= a) && (b <= c)) || ((b >= c) && (b <= a))) {
        printf("Middle: %d\n", b);
    } else if (((c >= a) && (c <= b)) || ((c >= b) && (c <= a))) {
        printf("Middle: %d\n", c);
    }
    
    return 0;
} 
