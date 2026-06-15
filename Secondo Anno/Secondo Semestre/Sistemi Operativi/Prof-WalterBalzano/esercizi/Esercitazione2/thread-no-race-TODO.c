#include <stdio.h>
#include <pthread.h>

int counter = 0;                 // variabile condivisa
pthread_mutex_t lock;            // mutex

void* thread_func(void* arg) {
    for (int i = 0; i < 100000; i++) {

        // entra in sezione critica
        pthread_mutex_lock(&lock);
        counter++;                   // accesso alla variabile condivisa
        pthread_mutex_unlock(&lock);
        // esce dalla sezione critica
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Counter finale: %d\n", counter);
    return 0;
}