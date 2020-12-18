// COMP1511 Week 4 Lab: Reverse an Array
//
// This program was written by Leon) WANG LIAO z5306312
// on 09/10/2020
//reads integers line by line
//when it reaches the end of input, 
//prints those integers in reverse order, line by line.

#include <stdio.h>
#define MAX_VALUE 100

void i_judge_loop(int array[MAX_VALUE]);

int main(void) {
    printf("Enter numbers forwards:\n");
    int array[MAX_VALUE] = {0};
    i_judge_loop(array);
}

// use scanf loop, i as a counter, 
// i can be used to count where we stop in the array
void i_judge_loop(int array[MAX_VALUE]) {
    int i = 0;
    while (scanf("%d\n", &array[i]) == 1) {
        i++;
    }

    printf("Reversed:\n");

    // use i-- to solve the reverse, 
    // form where we stop to where we start
    while (i > 0) {
        printf("%d\n", array[i - 1]);
        i--;
    }
}
