// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {

    int number;
    
    scanf("%d", &number);
    
    if (number < 0) {
        printf("Don't be so negative!\n");
    } else if (number > 0) {
        printf("You have entered a positive number.\n");
    } else {
        printf("You have entered zero.\n");
    }
    
    return 0;
}
