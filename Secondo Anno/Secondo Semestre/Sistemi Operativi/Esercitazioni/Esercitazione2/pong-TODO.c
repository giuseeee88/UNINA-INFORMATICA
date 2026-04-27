#include <pthread.h>
#include <stdio.h>

#define N 5

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;

int turno_ping = 1;

void* ping(void* arg) {
    for (int i = 1; i <= N; i++) {
        pthread_mutex_lock(&mtx);

        // TODO 1: aspettare finché non è il turno di ping
        while (turno_ping == 0) {
            pthread_cond_wait(&cv, &mtx);
        }

        printf("PING %d\n", i);
        turno_ping = 0;

        // TODO 2: svegliare l'altro thread
        pthread_cond_signal(&cv);

        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void* pong(void* arg) {
    for (int i = 1; i <= N; i++) {
        pthread_mutex_lock(&mtx);

        // TODO 3: aspettare finché non è il turno di pong
        while (turno_ping == 1) {
            pthread_cond_wait(&cv, &mtx);
        }

        printf("PONG %d\n", i);
        turno_ping = 1;

        // TODO 4: svegliare l'altro thread
        pthread_cond_signal(&cv);

        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, ping, NULL);
    pthread_create(&t2, NULL, pong, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}