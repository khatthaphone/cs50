#include<stdio.h>
#include<conio.h>

main() {
    
    float a, b, angle, radian, area;
    const float PI = 3.14159265;
    
    printf("This is a small program for calculating the surface area of a triangle.\nYou will need to provide 3 argument: length of a and b and the angle\n");
    
    printf("Enter a:");
    scanf("%f", &a);
        
    printf("Enter b:");
    scanf("%f", &b);
    
    printf("Enter angle:");
    scanf("%f", &angle);
    
    if (a > 0 && b > 0 && angle > 0 && angle < 180) {
        radian = angle * PI / 180;
        area = (radian * a * b) / 2;
        printf("Area = %f", area);
        
    } else {
        printf("The arguments you provided cannot be used to form an triangle.");
    }

}