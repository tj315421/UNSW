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
        while (column <= number) {// print 1 row includes num0 * column
            if (column == row || column == (number - row + 1)) {
                printf("*");
            } else {
                printf("-");
            }
            column ++;
        }                
        printf("\n");// print num0 * row 
        row ++;
    }
    
    return 0;
}

