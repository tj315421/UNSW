// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {
   
    int integer_n, integer_0 = 1, sum = 0;
    
    printf("Enter number: ");
    scanf("%d", &integer_n);
    
    printf("The factors of %d are:\n", integer_n);
    
    while (integer_0 <= integer_n) {
        if (integer_n % integer_0 == 0) {
            printf("%d\n", integer_0);
            //printf("The factors of %d are:\n%d\n",integer_n, integer_0);
            //--- wrong
            sum = sum + integer_0;
        }
        integer_0 ++;
    }
    
    printf("Sum of factors = %d\n", sum);
    // if i dont put \n it wont show the result. A bit confused here.
    
    if (sum % integer_n == 0) {
        printf("%d is a perfect number\n", integer_n);
    } else {
        printf("%d is not a perfect number\n", integer_n);
    }
    
    return 0;
}
