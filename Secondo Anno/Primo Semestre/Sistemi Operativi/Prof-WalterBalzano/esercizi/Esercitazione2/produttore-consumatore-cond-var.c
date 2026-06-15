#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;  // Indice di scrittura (produttore)
int out = 0; // Indice di lettura (consumatore)

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_full = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int item;
    for (int i = 0; i < 20; i++) {  // Esegue 20 produzioni per dimostrazione
        item = rand() % 100;  // Produce un valore casuale

        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&cond_not_full, &mutex);  // Attende se il buffer è pieno
        }

        // Inserisce l'elemento nel buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Producer produced: %d\n", item);

        // Segnala che il buffer non è vuoto
        pthread_cond_signal(&cond_not_empty);
        pthread_mutex_unlock(&mutex);

        sleep(1);  // Simula il tempo di produzione
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 20; i++) {  // Esegue 20 consumazioni per dimostrazione
        pthread_mutex_lock(&mutex);
        while (count == 0) {
            pthread_cond_wait(&cond_not_empty, &mutex);  // Attende se il buffer è vuoto
        }

        // Rimuove l'elemento dal buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumer consumed: %d\n", item);

        // Segnala che il buffer non è pieno
        pthread_cond_signal(&cond_not_full);
        pthread_mutex_unlock(&mutex);

        sleep(2);  // Simula il tempo di consumazione
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Crea il thread produttore
    pthread_create(&prod_thread, NULL, producer, NULL);

    // Crea il thread consumatore
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Attende la terminazione dei thread
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Distrugge il mutex e le variabili di condizione
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_not_empty);
    pthread_cond_destroy(&cond_not_full);

    return 0;
}
