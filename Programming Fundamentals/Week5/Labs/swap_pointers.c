// COMP1511 Week 5 Lab: Using pointers and a function to swap number values
//
// This program was written by Leon) WANG LIAO z5306312
// on 18/10/2020
//
// This program should take two pointers to integers as input,
// and swap the values stored in those two integers.
//

#include <stdio.h>

void swap_pointers(int *a, int *b);

// This is a simple main function which could be used
// to test your swap_pointers function.
// It will not be marked.
// Only your swap_pointers function will be marked.

int main(void) {
    int first = 1;
    int second = 2;
    
    swap_pointers(&first, &second);
    
    printf("%d, %d\n", first, second);
    return 0;
}

// swap the values in two integers, given as pointers
void swap_pointers(int *a, int *b) {
    // PUT YOUR CODE HERE (you must change the next line!)
    // set a temporay value;
    int temp;
    // swap values by using temporay value;
    temp = *a;
    *a = *b;
    *b = temp;
    
}
