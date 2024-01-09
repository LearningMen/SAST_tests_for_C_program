/*
    This program constructs a slightly more complicated memory leak scenario.
    The program allocates memory for an array of structs, each of which contains
    an inner array. 
    The program then initializes the inner arrays with values.
    The program then forgets to free the inner arrays before freeing the outer
    array, causing a memory leak.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* innerArray;
    int size;
} MyStruct;

int main() {
    int numStructs = 5; // Number of structs in the meta-array
    MyStruct **outerArray = (MyStruct**)malloc(numStructs * sizeof(MyStruct*));

    if (outerArray == NULL) {
        perror("Failed to allocate memory for outerArray");
        return 1;
    }

    // Allocate and initialize each struct and its inner array
    for (int i = 0; i < numStructs; ++i) {
        outerArray[i] = (MyStruct*)malloc(sizeof(MyStruct));
        if (outerArray[i] == NULL) {
            perror("Failed to allocate memory for outerArray element");
            // Free already allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(outerArray[j]->innerArray);
                free(outerArray[j]);
            }
            free(outerArray);
            return 1;
        }
        
        outerArray[i]->size = 10; // Size of the inner array
        outerArray[i]->innerArray = (int*)malloc(outerArray[i]->size * sizeof(int));
        if (outerArray[i]->innerArray == NULL) {
            perror("Failed to allocate memory for innerArray");
            // Free already allocated memory before exiting
            for (int j = 0; j <= i; j++) {
                free(outerArray[j]);
            }
            free(outerArray);
            return 1;
        }

        // Initialize the inner array with values
        for (int j = 0; j < outerArray[i]->size; j++) {
            outerArray[i]->innerArray[j] = j;
        }
    }

    // ... Use outerArray and its inner arrays ...

    // Free the meta-array but forget to free the inner arrays
    for (int i = 0; i < numStructs; ++i) {
        // Memory leak: innerArray not freed
        free(outerArray[i]); // Only freeing the struct, not its innerArray
    }
    free(outerArray);

    return 0;
}
