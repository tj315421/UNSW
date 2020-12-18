// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {

    int integer_1, integer_2;
    
    printf("Please enter two integers: ");
    scanf("%d %d", &integer_1, &integer_2);
    
    int sum = integer_1 + integer_2;
        
    printf("%d + %d = %d\n", integer_1, integer_2, sum);
    
    return 0;
}
