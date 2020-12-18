// COMP1511 Week 4 Lab: Circle Facts
//
// This program was written by Leon) WANG LIAO z5306312
// on 09/10/2020
//
// This program prints out facts about a circle given its radius,
// using functions.
//

#include <stdio.h>
#include <math.h>

double area(double radius);
double circumference(double radius);
double diameter(double radius);

// DO NOT CHANGE THIS MAIN FUNCTION
int main(void) {
    double radius;

    printf("Enter circle radius: ");
    scanf("%lf", &radius);

    printf("Area          = %lf\n", area(radius));
    printf("Circumference = %lf\n", circumference(radius));
    printf("Diameter      = %lf\n", diameter(radius));

    return 0;
}


// Calculate the area of a circle, given its radius.
double area(double radius) {
    // TODO: complete this function.
    double area = M_PI * radius * radius;
    return area; // TODO: change this to the correct return value.
}

// Calculate the circumference of a circle, given its radius.
double circumference(double radius) {
    // TODO: complete this function.
    double circumference = 2 * M_PI * radius;
    return circumference; // TODO: change this to the correct return value.
}

// Calculate the diameter of a circle, given its radius.
double diameter(double radius) {
    // TODO: complete this function.
    double diameter = 2 * radius;
    return diameter; // TODO: change this to the correct return value.
}
