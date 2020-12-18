// (Leon) WANG LIAO z5306312
/*
a=year%19
b=year/100
c=year%100
d=b/4
e=b%4
f=(b+8)/25
g=(b-f+1)/3
h=(19*a+b-d-g+15)%30
i=c/4
k=c%4
l=(32+2*e+2*i-h-k)%7
m=(a+11*h+22*l)/451
Easter Month =(h+l-7*m+114)/31  [3=March, 4=April]
p=(h+l-7*m+114)%31
Easter Date=p+1     (date in Easter Month)
*/
#include<stdio.h>
int main(void) {

    int year, a, b, c, d, e, f, g, h, i, k, l, m, p , easter_month, easter_date;
    
    printf("Enter year: ");
/*
scanf("%d%d%d%d", &a, &b, &c, &d); we cant use this form cuz it should be "2017", not "2 0 1 7".
*/
    scanf("%d", &year);
/*
    then i want to find a,b,c,d in terms of year.
*/
    
    a = year % 19;
    b = year / 100;
    c = year % 100;
    d = b / 4;
    e = b % 4;
    f = (b + 8) / 25;
    g = (b - f + 1) / 3;
    h = (19 * a + b - d - g + 15) % 30;
    i = c / 4;
    k = c % 4;
    l = (32 + 2 * e + 2 * i - h - k) % 7;
    m = (a + 11 * h + 22 * l) / 451; 
 /*
then i find the web gives me everything so that i dont have to think about them lol!
*/
    easter_month = (h + l - 7 * m + 114) / 31;
    
    printf("Easter is "); 
/*
according to the output we write this first then we start thinking about the month.
*/
    if (easter_month == 3) {
        printf("March ");
    } else if (easter_month == 4) { 
        printf("April ");
    } 
/*
only 2 options and the website gives us the fomulor. so we have dont the second printed part.
*/   
    p = (h + l - 7 * m + 114) % 31;
    easter_date = p + 1; 
/*
the third printed part is date which the website also tells us how to calculate.
*/   
    printf("%d in %d.\n", easter_date, year); 
/*
we just write done the final part of the output, care about the "." and " " and "\n" to make it looks clear.
*/
    
    return 0;
} 
// i think the wordAddition.c is more complicated than this question.
