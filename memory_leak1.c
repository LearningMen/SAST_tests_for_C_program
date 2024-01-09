#include <stdlib.h>

void func() {
    char *ptr = malloc(10); // Memory allocated and never freed
}

int main() {
    func();
    return 0;
}
