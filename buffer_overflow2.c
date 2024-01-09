#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate memory for 5 characters
    char *buffer = (char*)malloc(5 * sizeof(char));

    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Copy a string larger than 5 characters into the buffer
    strcpy(buffer, "This string is too long for the buffer");

    printf("%s\n", buffer);

    free(buffer);
    return 0;
}
