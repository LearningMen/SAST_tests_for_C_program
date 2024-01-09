#include <pthread.h>
#include <stdio.h>

volatile int counter = 0;  // Global counter

void* incrementCounter(void* arg) {
    for (int i = 0; i < 100000; ++i) {
        counter++;  // Direct increment without synchronization
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads that increment the counter
    pthread_create(&thread1, NULL, incrementCounter, NULL);
    pthread_create(&thread2, NULL, incrementCounter, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the final value of counter
    printf("Final counter value: %d\n", counter);
    return 0;
}
