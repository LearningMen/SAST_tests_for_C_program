#include <stdio.h>

int main() {
    char buf[100];
    scanf("%s", buf);
    printf(buf); // Format string vulnerability
    return 0;
}
