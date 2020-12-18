// (Leon) WANG LIAO z5306312
/*if (year is not divisible by 4) then (it is a common year)
    else if (year is not divisible by 100) then (it is a leap year)
    else if (year is not divisible by 400) then (it is a common year)
    else (it is a leap year)
    */
#include <stdio.h>

int main (void) {
    
    int year;
    
    printf("Enter year: ");
    scanf("%d", &year);
    
    if (year % 4 != 0) {
        printf("%d is not a leap year.\n", year);
    } else if (year % 100 != 0) {
        printf("%d is a leap year.\n", year);
    } else if (year % 400 != 0) {
        printf("%d is not a leap year.\n", year);
    } else {
        printf("%d is a leap year.\n", year);
    }
    
    return 0;
}
