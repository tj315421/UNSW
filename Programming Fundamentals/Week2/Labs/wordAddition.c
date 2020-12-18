// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {

    int number_1, number_2, sum;
    
    printf("Please enter two integers: ");
    scanf("%d %d", &number_1, &number_2);
    
    sum = number_1 + number_2;
        
    if (number_1 < 0 && number_1 >= -10) {
        printf("negative ");
        number_1 = number_1 * (-1);
    }
   
    if (number_1 == 0) {
        printf("zero");
    } else if (number_1 == 1) {
        printf("one");
    } else if (number_1 == 2) {
        printf("two");
    } else if (number_1 == 3) {
        printf("three");
    } else if (number_1 == 4) {
        printf("four");
    } else if (number_1 == 5) {
        printf("five");
    } else if (number_1 == 6) {
        printf("six");
    } else if (number_1 == 7) {
        printf("seven");
    } else if (number_1 == 8) {
        printf("eight");
    } else if (number_1 == 9) {
        printf("night");
    } else if (number_1 == 10) {
        printf("ten");
    }
    if (number_1 > 10 || number_1 < -10 ) {
        printf("%d", number_1);
    }
        
    printf(" + ");
    
    if (number_2 < 0 && number_2 >= -10) {
        printf("negative ");
        number_2 = number_2 * (-1);
    }
   
    if (number_2 == 0) {
        printf("zero");
    } else if (number_2 == 1) {
        printf("one");
    } else if (number_2 == 2) {
        printf("two");
    } else if (number_2 == 3) {
        printf("three");
    } else if (number_2 == 4) {
        printf("four");
    } else if (number_2 == 5) {
        printf("five");
    } else if (number_2 == 6) {
        printf("six");
    } else if (number_2 == 7) {
        printf("seven");
    } else if (number_2 == 8) {
        printf("eight");
    } else if (number_2 == 9) {
        printf("night");
    } else if (number_2 == 10) {
        printf("ten");
    }
    if (number_2 > 10 || number_2 < -10 ) {
        printf("%d", number_2);
    }        
    printf(" = ");
        
    if (sum < 0 && sum >= -10) {
        printf("negative ");
        sum = sum * (-1);
    }
   
    if (sum == 0) {
        printf("zero");
    } else if (sum == 1) {
        printf("one");
    } else if (sum == 2) {
        printf("two");
    } else if (sum == 3) {
        printf("three");
    } else if (sum == 4) {
        printf("four");
    } else if (sum == 5) {
        printf("five");
    } else if (sum == 6) {
        printf("six");
    } else if (sum == 7) {
        printf("seven");
    } else if (sum == 8) {
        printf("eight");
    } else if (sum == 9) {
        printf("night");
    } else if (sum == 10) {
        printf("ten");
    }        
    if (sum > 10 || sum < -10 ) {
        printf("%d", sum);
    }
    
    printf("\n");
        
    return 0;
}
