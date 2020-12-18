// COMP1511 Week 4 Lab: Calculator
//
// This program was written by Leon) WANG LIAO z5306312
// on 09/10/2020
//
#include <math.h>
#include <stdio.h>

void print_words();
void scanf_loop(int number);

#define JUDGE_1 1
#define JUDGE_2 2

int main() {
    int number = -1;
    print_words();
    scanf_loop(number);
}

// creat a print function which will be used twice 
void print_words() {
    printf("Enter instruction: ");
}

// using the comparison of scanf and 1 to achieve a loop of printf
void scanf_loop(int number) {
    while (scanf("%d", &number) == 1) {
    
        if (number == JUDGE_1) {
            int result1;
            scanf("%d", &number);
            result1 = number * number;
            printf("%d\n", result1);
        } else if (number == JUDGE_2) {
            int result2, number1;
            scanf("%d", &number);
            number1 = number;
            scanf("%d", &number);
            result2 = pow(number1, number);
            printf("%d\n", result2);
        }
        
        print_words();
    }
}
