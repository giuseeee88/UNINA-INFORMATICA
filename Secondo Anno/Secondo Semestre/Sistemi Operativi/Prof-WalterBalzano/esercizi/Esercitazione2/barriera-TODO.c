#include <pthread.h>
#include <stdio.h>

#define T 5

int arrivati = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

void barrier_wait() {
    pthread_mutex_lock(&mtx);

    // TODO 1:
    // incrementare il numero di thread arrivati alla barriera
    arrivati++;

    if (arrivati == T) {
        // TODO 2:
        // risvegliare tutti i thread bloccati sulla barriera
        pthread_cond_broadcast(&cv);
    } else {
        // TODO 3:
        // aspettare finché non sono arrivati tutti i thread
        while (arrivati < T) {
            pthread_cond_wait(&cv, &mtx);
        }
    }

    pthread_mutex_unlock(&mtx);
}

void* worker(void* arg) {
    int id = *(int*)arg;

    printf("Thread %d: fase 1\n", id);

    barrier_wait();

    printf("Thread %d: fase 2\n", id);
    return NULL;
}

int main() {
    pthread_t th[T];
    int ids[T];

    for (int i = 0; i < T; i++) {
        ids[i] = i;
        pthread_create(&th[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < T; i++) {
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);

    return 0;
}