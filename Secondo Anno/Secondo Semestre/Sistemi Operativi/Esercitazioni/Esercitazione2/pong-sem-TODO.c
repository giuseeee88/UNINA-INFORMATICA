#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5

sem_t sem_ping;
sem_t sem_pong;

void* ping(void* arg) {
    for (int i = 1; i <= N; i++) {

        // TODO 1:
        // aspettare il proprio turno
        sem_wait(&sem_ping);

        printf("PING %d\n", i);

        // TODO 2:
        // sbloccare il thread pong
        sem_post(&sem_pong);
    }

    return NULL;
}

void* pong(void* arg) {
    for (int i = 1; i <= N; i++) {

        // TODO 3:
        // aspettare il proprio turno
        sem_wait(&sem_pong);

        printf("PONG %d\n", i);

        // TODO 4:
        // sbloccare il thread ping
        sem_post(&sem_ping);
    }

    return NULL;
}

int main() {
    pthread_t t1, t2;

    // TODO 5:
    // inizializzare i semafori in modo che ping parta subito
    // e pong aspetti
    sem_init(&sem_ping, 0, 1);
    sem_init(&sem_pong, 0, 0);

    pthread_create(&t1, NULL, ping, NULL);
    pthread_create(&t2, NULL, pong, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // TODO 6:
    // distruggere i semafori
    sem_destroy(&sem_ping);
    sem_destroy(&sem_pong);

    return 0;
}