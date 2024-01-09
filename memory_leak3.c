/*
    This program leaks memory but only in one of the if branch.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Allocate memory
    char *buffer = (char*)malloc(sizeof(char));
    if (buffer == NULL) {
        return 2; // Return 2 in case memory allocation fails
    }

    // Open a common file
    FILE *file = fopen("/etc/passwd", "r");
    if (file == NULL) {
        return -1; // Return -1 and leak memory if file opening fails
    }

    // Read the first character
    char firstChar = fgetc(file);
    if (firstChar != EOF) {
        *buffer = firstChar;
        printf("First character in file: %c\n", *buffer);
    }

    // Close file and free memory
    fclose(file);
    free(buffer);

    return 0;
}
