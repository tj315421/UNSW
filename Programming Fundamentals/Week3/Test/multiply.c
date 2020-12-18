// // (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {
    
    int number1, number2;
    int abs_value;
    
    scanf("%d %d", &number1, &number2);

    abs_value = number1*number2;
    
    if (abs_value > 0) {
        printf("%d\n", abs_value);
    } else if (abs_value < 0) {
        abs_value = -abs_value;
        printf("%d\n", abs_value);
    } else {
        printf("zero\n");
    }
    
    return 0;
}
