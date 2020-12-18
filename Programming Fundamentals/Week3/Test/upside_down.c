// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {
    
    double number1, number2, number3;
    
    printf("Please enter three numbers: ");
    
    scanf("%lf %lf %lf", &number1, &number2, &number3);
    
    if (number1 < number2 && number2 < number3) {
        printf("up\n");
    } else if (number1 > number2 && number2 > number3) {
        printf("down\n");
    } else {
        printf("neither\n");
    }

    return 0;
}
