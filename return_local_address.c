#include <stdio.h>

char* getLocalString() {
    char localString[] = "Hello, World!";
    return localString; // Warning: returning address of local variable
}

int main() {
    char *str = getLocalString();
    printf("%s\n", str); // Undefined behavior: str points to deallocated stack memory
    return 0;
}
