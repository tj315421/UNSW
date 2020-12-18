// (Leon) WANG LIAO z5306312
#include <stdio.h>

// return the number of "bigger" values in an array (i.e. larger than 99
// or smaller than -99).
int count_bigger(int length, int array[]) {
    // PUT YOUR CODE HERE (you must change the next line!)
    int counter = 0;
    int val_nums = 0;
    while (counter < length) {
        if (array[counter] < -99 || array[counter] > 99) {            
            val_nums++;
        }
        counter++;
    }
    
    return val_nums;
}

// This is a simple main function which could be used
// to test your count_bigger function.
// It will not be marked.
// Only your count_bigger function will be marked.

#define TEST_ARRAY_SIZE 8

int main(void) {
    int test_array[TEST_ARRAY_SIZE] = {141, 5, 92, 6, 535, -89, -752, -3};

    int result = count_bigger(TEST_ARRAY_SIZE, test_array);

    printf("%d\n", result);
    return 0;
}
