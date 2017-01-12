#include <stdio.h>

int main(void) {
    printf("Enter your name:\n");

    // Declare a string buffer for reading
    char name[30];

    // Read String
    scanf("%30s", name);

    // Print String
    printf("Hello %s\n", name);

    return 0;
}
