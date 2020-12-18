// COMP1511 Week 4 test: Print a Distance Square
//
// This program was written by Leon) WANG LIAO z5306312
// on 09/10/2020
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main(void) {
    int number;
    printf("Enter square size: ");
    scanf("%d", &number);

    int row = 1;
    while (row <= number) {
        int column = 1;
        while (column <= number) {
            int n, c;
            
            n = (number + 1) / 2;
            c = abs(column - n) + abs(row - n);
            
            printf("%2d", c);
            
            column++;
        }
        printf("\n");
        row++;
    }

    return 0;
} 
// REFLECT:
    /*
    I wasted a lot of time with the usage of "\n" and " " in Ques 1 and 2,
    when deal with question 2,
    I write down below immediately,
    
    int i = 1, num;
    int sum = 0;
    while (i <= number ) {
        scanf("%d", &num);
        sum = sum + num;
        i++;
    }
    
    printf("The sum is: %d\n", sum);
    
    However, i didnt write down the "\n" in the last lane.
    So when i tested it, if i input n numbers there, 
    i always have to scanf (n + 1) numbers to make the last step work.
    So i wasted a lot of time and became very nervous.
    
    In question 3,
    at that time my mind was messy, because i always cant hold mysely
    Looking at the remaining time limit.
    I just want to solve it step by step to get sufficient points,
    so my logic becames really separated, 
    i cant focus myself into that question.
    
    After the time up, i found it is just about the difference of
    the column and row between the mid point and a random point.
    I only take 2 mins to write dowmn code below.
    
    n = (number + 1) / 2;
    c = abs(column - n) + abs(row - n);
    
    And use the absolute value to make it easy to express.
    Things become easier when i dont have time limtitation.
    Maybe i should try to practice my psychological quality,
    and also the coding speed!
    */

    
    
