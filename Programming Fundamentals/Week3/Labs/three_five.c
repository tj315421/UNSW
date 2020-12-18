// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {
    int integer_n, integer_0 = 1;
    
    printf("Enter number: ");
    scanf("%d", &integer_n);
    
    while (integer_0 < integer_n) {
        //printf("1");
        if (integer_0 % 3 == 0 || integer_0 % 5 == 0) {
            printf("%d\n", integer_0);
            
            //integer_0++;---WRONG POSITION :(
        }
        integer_0++;
    }
    return 0;
}
