#include <stdio.h>

int main() {
    int array[5] = {1, 2, 3, 4, 5};

    // Correctly accessing the array
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Accessing array out of bounds - Undefined behavior
    printf("Accessing out of bounds: %d\n", array[5]);

    return 0;
}
