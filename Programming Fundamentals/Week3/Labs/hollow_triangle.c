// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {

    int number;
    int row, column;
    
    printf("Enter size: ");
    scanf("%d", &number);
    
    row = 1;
    while (row <= number) {
        column = 1;
        while (column <= row) {
            if (column == 1 || column == row) {
                printf("*");
            } else if (row == number) {
                printf("*");
            } else {
                printf(" ");
            }
            column ++;
        }
        printf("\n");
        row ++;
    }
    return 0;
}
