// (Leon) WANG LIAO z5306312
#include<stdio.h>
int main(void) {
    int number_sides, number_dice;
    
    printf("Enter the number of sides on your dice: ");
    scanf("%d", &number_sides);
    
    printf("Enter the number of dice being rolled: ");
    scanf("%d", &number_dice);
    
    if (number_sides <= 0 || number_dice <= 0) {
        printf("These dice will not produce a range.\n");
    } else {
        double min_range = number_dice;
        double max_range = number_dice * number_sides;
    
        printf("Your dice range is %.0lf to %.0lf. \n", min_range, max_range);
    
        double average_value = (min_range + max_range) / 2;
    
        printf("The average value is %.6lf\n", average_value);
    }
    
    return 0;
}
