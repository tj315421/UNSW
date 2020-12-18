// COMP1511 Week 4 Lab: Painter Bot
//
// This program was written by Leon) WANG LIAO z5306312
// on 09/10/2020
//
// This program scan in indices until EOF 
// and then print out a one dimensional canvas which has 36 '0's,
// except at the given indices it has a '1'.
// using functions.

#include <stdio.h>
#define ARRAY_SIZE 36

void replace_one(int array[ARRAY_SIZE]);
void print_canvas(int array[ARRAY_SIZE]);

int main(void) {
    // build a 36 * 0 base canvas 
    int array[ARRAY_SIZE] = {0};
    
    replace_one(array);
    print_canvas(array);
}

// replace 0 with 1 at where we enter the numbers.
void replace_one(int array[ARRAY_SIZE]) {
    int number;
    // ret_val to represent the value of scanf("%d", &number)
    // in order to make the relacement of 1 match each scan
    int ret_val = scanf("%d", &number);
    // using if to make code continues when face to " "
    // without if, when we enter " ", " " is not a int
    if (ret_val == 1) {
        // replace 0, match each scan.
        array[number] = 1;
     
        while (ret_val == 1) { 
            ret_val = scanf("%d", &number); 
            array[number] = 1;
        }
    }
}

// print the whole canvas from 0 to 35
void print_canvas(int array[ARRAY_SIZE]) {
    int i = 0;
    while (i < ARRAY_SIZE) {
        printf("%d ", array[i]);
        i++;
    }
    printf("\n");
}
