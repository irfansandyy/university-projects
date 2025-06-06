#include <stdio.h>

int main() {
    const float pi = 3.14159f;
    float base;
    float base1;
    float base2;
    float height;
    float side_length;
    float radius;

    printf("Input Base: ");
    scanf(" %f", &base);
    printf("Input Base1: ");
    scanf(" %f", &base1);
    printf("Input Base2: ");
    scanf(" %f", &base2);
    printf("Input Height: ");
    scanf(" %f", &height);
    printf("Input Side Length: ");
    scanf(" %f", &side_length);
    printf("Input Radius: ");
    scanf(" %f", &radius);
    
    printf("Area of a Rectangle: %.2f", base * height);
    printf("\nArea of a Square: %.2f", side_length * side_length);
    printf("\nArea of Triangle: %.2f", base * height / 2);
    printf("\nArea of Parallelogram: %.2f", base * height);
    printf("\nArea of Trapezoid: %.2f", (base1 + base2) * height / 2);
    printf("\nArea of Circle: %.2f", pi * radius * radius);

    return 0;
}