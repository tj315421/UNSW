//30/09/2020
// (Leon) WANG LIAO z5306312
/*
#include<stdio.h>
int main(void) {
   
    int n;
    int row, column;
    
    printf("Enter size: ");
    scanf("%d", &n);
    
    
    row = n;
    while (row >= 1) {
        column = 1;
        } else if (column <= n) {
            if (column == n + 1 - row || column % 2 != 0) {
                printf("*");
            } else if (column == n + 1 - row || column % 2 == 0){     
                printf("-");
              }
            column ++;
        }
        printf("\n");
        row --;
    }
    */
    
    /*
    row = 1;
    while (row <= n) {
        column = n;
        while (column >= 1) {
            if (row == 1 || row == n) {
                printf("*");
            } else if (column == n + 1 - row || column % 2 != 0) {
                printf("*");
            } else if (column) {
            //if (column == n + 1 - row || column % 2 == 0) {
                printf("-");
            }
            column --;
        }
        printf("\n");
        row ++;//print n row
    }
    return 0;
}
*/
/*
//01/10/2020
// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main() {
    
    // firstly, bulid the base --- 1st idea, wanna change something on a base, but cant achieve.
    // then i chose to find the law, still failed, so i chose to find the law of each column & row. and it seems working.

    int number, row, column;
    
    printf("Enter size: ");
    scanf("%d", &number);
    
    row = 1;
    while (row <= number) {
        column = 1;
        while (column <= number) {
            if (row == 1 || row == number) {
                printf("*");
            } else if (column == number) {
                printf("*");
            } else if (column == number-1) {
                printf("-");
            } else if (row % 2 != 0) {
                printf("*");
            } 
            // below this lane are important.
              else if (row != 2 && column == 1) { 
                printf("*");
            } else {
                printf("-");
            }
        column ++;
        }
        printf("\n");
        row ++;    
    }
    return 0;
}   
*/
    /* 
    ********* 1 1-9       || 0
    --------* 2 9         || 1-8   
    *******-* 3 1-7,9     || 8
    *-----*-* 4 1,7,9     || 2-6,8
    *-***-*-* 5 1,3-5,7,9 || 2,6,8
    *-*---*-* 6 1,3,7,9   || 2,4-6,8
    *-*****-* 7 1,3-7,9   || 2,8
    *-------* 8 1,9       || 2-8
    ********* 9 9         || 0


    ********* 
    --------*
    *******-*
    *-------* *-----*-* 4
    *******-* *-***-*-* 5
    *-------* *-*---*-* 6
    *******-* *-*****-* 7
    *-------*
    *********
    */
/*   
//02/10/2020
//    for column = 1 -> (n - 1) / 2 && row = 3 -> n , if column % 2 != 0, "*"
//       then row = 4 -> n - 1... (what i was confused with)
//    for column = n -> (n + 1) / 2 && row = 1 -> n , if column % 2 == 0, "-"
//        then row = 2 -> n - 1... 
//    for row <= 2, if row = 1 && column <= n - 1, "*"
//                    , if row = 2 && column <= n - 2, "-"
#include<stdio.h>
int main(void) {
    
    int n, row, column;// n means 'number'
        
    printf("Enter size: ");
    scanf("%d", &n);
    
    //int top_side = (n+1)/2, bot_side = (n-1)/2;
        
    row = 1;//, top_side = 1, bot_side = n;
    while (row <= n) {
        column = 1;
        while (column <= n) {
            
            if (row == 1 && column <= n - 1) {
                printf("*");
            } else if (row == 2 && column <= n - 2) {
                printf("-");
            } 
  
            else if ((row >= 1 && row <= n) 
            && (column >= (n + 1) / 2 && column <= n)) { 
                //top_side = 1, bot_side = n; 
                //while ()
                if ((column % 2 != 0) || (row % 2 != 0)) {
                    printf("*");
                } else if ((column % 2 == 0) || (row % 2 == 0)) {
                    printf("-");
                }
          //printf("%d %d %d ", n, row, column);
                //while () {
                 //   printf("\n");
                  //  top_side ++;
                  //  bot_side --;
            } 
            
            else if ((row >= 3 && row <= n) 
            && (column >= 1 && column <= (n - 1) / 2 )) {
                if ((column % 2 != 0) || (row % 2 != 0)) {
                    printf("*");
                } else if ((column % 2 == 0) || (row % 2 == 0)) {
                    printf("-");
                }
            }
            
            //printf(" ");
            column ++; 
            }
            
        printf("\n");
        row ++;
        }
   
    return 0;
}
*/
/*
#include<stdio.h>
int main(void) {
    
    int n, row, column;
        
    printf("Enter size: ");
    scanf("%d", &n);
    

        
    row = 1
    while (row <= n) {
        column = 1;
        while (column <= n) {
            
            if ((row == 1 && column <= n - 1) || (column == n) || (row >= 3 && column == 1)) {
                printf("*");
            } 

            else if ((row >= 4 && row <= n - 1) && (column == 2)) {
            printf("-");
            } else if ((row >= 5 && row <= n - 2) && (column == 3)) {
            printf("*");
            } else if ((row >= 6 && row <= n - 3) && (column == 4)) {
            printf("-");
            }

            else if ((row >= 2 && row <= n - 1) && (column == n - 1)) {
            printf("-");
            } else if ((row >= 3 && row <= n - 2) && (column == n - 2)) {
            printf("*");
            } else if ((row >= 4 && row <= n - 3) && (column == n - 3)) {
            printf("-");
            } else if ((row == (n+1) / 2) && (column == (n+1) / 2)) {
            printf("*");
            } else if (row % 2 == 0) {
                printf("-");
            } else if (row % 2 != 0) {
                printf("*");
            }
            /*
            else if ((row >= 4 && row <= 8) && (column == 2)) {
            printf("-");
            } else if ((row >= 5 && row <= n - 2) && (column == n - 6)) {
            printf("*");
            } else if ((row == 6 && row == n - 3) && (column == n - 5)) {
            printf("-");
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
*/
/*


*****************
----------------*
***************-*
*-------------*-*4
*-***********-*-*5
*-*---------*-*-*6
*-*-*******-*-*-*7
*-*-*-----*-*-*-*8
*-*-*-***-*-*-*-*9
*-*-*-*---*-*-*-*10
*-*-*-*****-*-*-*11
*-*-*-------*-*-*12
*-*-*********-*-*13
*-*-----------*-*14
*-*************-*15
*---------------*16
*****************

*****************
----------------*
***************-*
*-------------*-*
*-***********-*-*
*-*---------*-*-*
*-*-*******-*-*-*
*-*-*-----*-*-*-*
*-*-*-***-*-*-*-*
*-*-*-*--*-*-*-*
*-*-*-**-*-*-*
*-*-*---*-*-*
*-*-*****-*-*
*-*-------*-*
*-*********-*
*-----------*
*****************
*/
#include<stdio.h>
int main(void) {
    
    int n, row, column;
    
    int i, j, m;
    int a, b, c;
    int x, y, z;
    int p, q, k;
    
    printf("Enter size: ");
    scanf("%d", &n);
    

        
    row = 1;
    while (row <= n) {
        column = 1;
        while (column <= n) {
            
            if ((row == 1 && column <= n - 1) || (column == n) || (row >= 3 && column == 1)||(row == n)) {
                printf("*");
            }
                    
            i = 4 , m = 1, j = 2;
            while ((i <= (n + 1) / 2) || (m <= (n - 5) / 2) || (j <= (n - 1) / 2)) {
                if ((row >= i && row <= n - m) 
                && (column == j && column % 2 == 0)) {
                    printf("-");
                } else if ((row >= i && row <= n - m) 
                && (column == j && column % 2 != 0)) {
                    printf("*");
                }
                i ++;
                m ++;
                j ++;
            }
            
            
            a = 2, b = 1, c = 1;
            while ((a <= (n - 1) / 2) || (b <= (n + 1) / 2) || (c <= (n + 1) / 2)) {
                if ((row >= a && row <= n - b) 
                && (column == (n - c) && column % 2 == 0)) {
                    printf("-");
                } else if ((row >= a && row <= n - b) 
                && (column == (n - c) && column % 2 != 0)) {
                    printf("*");
                }
                a ++;
                b ++;
                c ++;
            }
            
            x = 2, y = 2, z = 1;
            while ((x <= (n - 1) / 2) || (y <= (n - 1) / 2) || (z <= (n + 3) / 2)) {
                if ((row == x && row % 2 == 0) && (column >= y && column <= n - z)) {
                printf("-");
            } else if ((row == x && row % 2 != 0) && (column >= y && column <= n - z)) {
                printf("*");
            } 
                x ++;
                y ++;
                z ++;
            } 
            
            
            p = 1, q = 4, k = 1;
            while ((p <= (n - 3) / 2) || (q <= (n - 1) / 2) || (k <= (n-3) / 2)) {
                if ((row == n - p && row % 2 == 0) 
                && (column >= q && column <= n - k)) {
                printf("-");
            } else if ((row == n - p && row % 2 != 0) 
                && (column >= q && column <= n - k)) {
                printf("*");
            }
                p ++;
                q ++;
                k ++;
            
            }
           
            

            
            /*
            if ((row == 2) && (column >= 2 && column <= n-1)) {
                printf("-");
            } else if ((row == 3) && (column >= 3 && column <= n-2)) {
                printf("*");
            } else if ((row == 4) && (column >= 4 && column <= n-3)) {
                printf("-");
            } else if ((row == (n+1)/2 ) && (column == (n+1)/2)) {
                printf("*");
            } else if ((row == n-1) && (column >= 4 && column <= n-1)) {
                printf("-");
            } else if ((row == n-2) && (column >= 5 && column <= n-2)) {
                printf("*");
            } else if ((row == n-3) && (column >= 6 && column <= n-3)) {
                printf("-");
            } 
            */
                        column ++; 
            }
            
        printf("\n");
        row ++;
        }
   /*
            else if ((row >= 2 && row <= n - 1) && (column == n - 1)) {
            printf("-");
            } else if ((row >= 3 && row <= n - 2) && (column == n - 2)) {
            printf("*");
            } else if ((row >= (n-1)/2 && row <= n - 3) && (column == n - 3)) {
            printf("-");
            } else if ((row == (n+1) / 2) && (column == (n+1) / 2)) {
            printf("*");
            } 
            
            else if (row % 2 == 0) {
                printf("-");
            } else if (row % 2 != 0) {
                printf("*");
            }*/
    return 0;
}
