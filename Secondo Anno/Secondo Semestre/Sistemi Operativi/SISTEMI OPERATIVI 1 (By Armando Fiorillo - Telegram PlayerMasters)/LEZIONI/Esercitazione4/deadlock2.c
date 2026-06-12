#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

void* thread1_func(void* arg) {
    printf("Thread 1: Tentando di acquisire mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: mutex1 acquisito.\n");

    // Simula lavoro
    sleep(1);

    printf("Thread 1: Tentando di acquisire mutex2...\n");
    pthread_mutex_lock(&mutex2);  // Potenziale deadlock se thread 2 ha mutex2
    printf("Thread 1: mutex2 acquisito.\n");

    // Simula operazione
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
    pthread_mutex_lock(&mutex1);  // Potenziale deadlock se thread 1 ha mutex1
    printf("Thread 2: mutex1 acquisito.\n");

    // Simula operazione
    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex2);

    return NULL;
}

void* thread3_func(void* arg) {
    printf("Thread 3: Tentando di acquisire mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 3: mutex1 acquisito.\n");

    // Simula lavoro
    sleep(1);

    printf("Thread 3: Tentando di acquisire mutex2...\n");
    pthread_mutex_lock(&mutex2);  // Potenziale deadlock se thread 2 ha mutex2
    printf("Thread 3: mutex2 acquisito.\n");

    // Simula operazione
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

int main() {
    pthread_t t1, t2, t3;

    // Crea i thread
    pthread_create(&t1, NULL, thread1_func, NULL);
    pthread_create(&t2, NULL, thread2_func, NULL);
    pthread_create(&t3, NULL, thread3_func, NULL);

    // Aspetta che i thread finiscano
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}