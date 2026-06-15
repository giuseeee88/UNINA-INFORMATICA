#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* thread1_func(void* arg) {
    printf("Thread 1: Tentando di acquisire mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: mutex1 acquisito.\n");

    // Simula lavoro
    sleep(1);

    printf("Thread 1: Tentando di acquisire mutex2...\n");
    pthread_mutex_lock(&mutex2);  // Qui il deadlock si verifica se thread 2 ha già mutex2
    printf("Thread 1: mutex2 acquisito.\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

void* thread2_func(void* arg) {
    printf("Thread 2: Tentando di acquisire mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: mutex2 acquisito.\n");

    // Simula lavoro
    sleep(1);

    printf("Thread 2: Tentando di acquisire mutex1...\n");
    pthread_mutex_lock(&mutex1);  // Qui il deadlock si verifica se thread 1 ha già mutex1
    printf("Thread 2: mutex1 acquisito.\n");

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Crea i thread
    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);

    // Aspetta che entrambi i thread finiscano
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
