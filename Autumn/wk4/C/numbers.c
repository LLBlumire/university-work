#include<stdio.h>
#include<stdint.h>

int main(void) {
    // Hardcoding of Integer Values
    int32_t num = 8;
    int32_t den = 3;

    // Division and Modulus of Hardcoded Integer Values
    printf("%d divided by %d = %dr%d\n", num, den, num / den, num % den);

    // User Input of Integer Values
    printf("Enter an integer numerator:\n");
    scanf("%d", &num);
    printf("Enter an integer denominator:\n");
    scanf("%d", &den);

    // Division of Input Integer Values
    printf("%d divided by %d = %dr%d\n", num, den, num / den, num % den);

    // Buffer Types for Input Floatng Point Values
    float num_f;
    float den_f;

    // User Input of Floating Point Values
    printf("Enter a float numerator:\n");
    scanf("%f", &num_f);
    printf("Enter a float denominator:\n");
    scanf("%f", &den_f);

    // Division of Input Floating Point Values
    printf("%f divided by %f = %f\n", num_f, den_f, num_f / den_f);
}
