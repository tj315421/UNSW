// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {

    int number1, number2, number3;

    printf("Enter integer: ");
    scanf("%d", &number1);
    
    printf("Enter integer: ");
    scanf("%d", &number2);
    
    printf("Enter integer: ");
    scanf("%d", &number3);
    
    
    printf("The integers in order are: %d %d %d\n",
     
    (number1 < number2) * (number1 <= number3) * number1 
    + (number2 <= number1) * (number2 <= number3) * number2 
    + (number3 <= number1) * (number3 < number2) * number3,
     
    ((number1 <= number3 && number1 > number2 ) 
    || (number1 < number2 && number1 >= number3)) * number1 
    + ((number2 <= number3 && number2 >= number1 ) 
    || (number2 <= number1 && number2 >= number3)) * number2 
    + ((number3 < number1 && number3 >= number2 ) 
    || (number3 <= number2 && number3 > number1)) * number3,
     
    (number1 > number2) * (number1 > number3) * number1 
    + (number2 >= number1) * (number2 >= number3) * number2 
    + (number3 >= number1) * (number3 > number2) * number3);
    
    return 0;
}
