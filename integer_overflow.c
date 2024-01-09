#include <stdio.h>
#include <limits.h>

int main() {
    int max_int = INT_MAX;
    int result = max_int + 1; // integer overflows!

    printf("Max int: %d\n", max_int);
    printf("Max int + 1: %d\n", result); // result is a negative number!

    return 0;
}