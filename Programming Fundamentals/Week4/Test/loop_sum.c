// COMP1511 Week 4 test: Loop Sum
//
// This program was written by Leon) WANG LIAO z5306312
// on 09/10/2020
#include<stdio.h>
int main(void) {
    int number;
    
    printf("How many numbers: ");
    scanf("%d", &number);
    
    int i = 1, num;
    int sum = 0;
    while (i <= number ) {
        scanf("%d", &num);
        sum = sum + num;
        i++;
    }
    
    printf("The sum is: %d\n", sum);
    
    return 0;
} 
