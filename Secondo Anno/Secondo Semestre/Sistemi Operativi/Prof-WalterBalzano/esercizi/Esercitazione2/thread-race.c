#include <stdio.h>
#include <pthread.h>

int counter = 0;                 // variabile condivisa


void* thread_func(void* arg) {
    for (int i = 0; i < 100000; i++) {

        counter++;                   // accesso alla variabile condivisa


    }
    return NULL;
}

int main() {
    pthread_t t1, t2;


    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);


    printf("Counter finale: %d\n", counter);
    return 0;
}