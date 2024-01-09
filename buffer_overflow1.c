#include <stdio.h>
#include <string.h>

int main() {
    char buffer[10];
    // This line deliberately causes a buffer overflow
    strcpy(buffer, "This string is way too long for the buffer");
    printf("%s\n", buffer);
    return 0;
}
