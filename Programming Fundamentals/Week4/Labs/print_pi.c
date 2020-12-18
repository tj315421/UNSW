//09/10/2020
// (Leon) WANG LIAO z5306312
// Prints the first n digits of pi, where n is specified 
// by the user

#include<stdio.h>

#define MAX_DIGITS 10

void print_out_1(int pi[MAX_DIGITS]);
void print_out_loog(int number, int pi[MAX_DIGITS]);
int scan_input(int input);
void print_zero();

int main(void) {
    int pi[MAX_DIGITS] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    printf("How many digits of pi would you like to print? ");
    //TODO: Insert your code here
    int input = -1;
    int number = scan_input(input);
    
    if (number == 1) {
        print_out_1(pi);
    } else if (number >= 1 && number <= 10) {
        print_out_loog(number, pi);
    } else if (number < 1) {
        print_zero();
    }
      
    return 0;
}


// scan a number 
int scan_input(int input) {
    scanf("%d", &input);
    return input;
}

// print when number = 1
void print_out_1(int pi[MAX_DIGITS]) {
    printf("%d\n", pi[0]);
}

// print when number >= 1 && number <= 10
void print_out_loog(int number, int pi[MAX_DIGITS]) {
    printf("%d.", pi[0]);
    int i = 1;
    while (i < number) {
        printf("%d", pi[i]);
        i++;
    } 
    printf("\n");
}

// print when number <=0
void print_zero() {
    printf("\n");
}
