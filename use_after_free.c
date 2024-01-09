#include <stdio.h>

int main() {
    char *buffer = (char*)malloc(100 * sizeof(char));
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Use the buffer for some operation
    sprintf(buffer, "Sample text for buffer.");

    // Free the buffer
    free(buffer);

    // Use after free - dangerous!
    printf("Buffer content after free: %s\n", buffer);

    return 0;
}