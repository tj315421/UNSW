// A simple C program that attempts to be punny
// Written 23/2/2017
// by Angela Finlayson (angf@cse.unsw.edu.au)
// for COMP1511 Lab 01 Exercise 1

/* 
in linux system highlight + mid button = ctrl c + v
*/


#include <stdio.h>
#include <stdlib.h>
void recursive_d(int array[128], int i);
int main (void) {
    int array[128] = {0};
    int i = 7;
    recursive_d(array, i);
    printf("%d", i);
    return 0;
}

// assume array is a valid array of integers,
// assume i is any integer.
void recursive_d(int array[128], int i) {
    if (i < 0) {
        return;
    }
    array[i] = i;
    recursive_d(array, i - 1);
}

