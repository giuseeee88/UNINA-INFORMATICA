#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0;  // Indice di scrittura (produttore)
int out = 0; // Indice di lettura (consumatore)

// Semafori
sem_t empty_slots;  // Conta gli slot vuoti disponibili nel buffer
sem_t filled_slots; // Conta gli slot pieni nel buffer
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex per proteggere l'accesso al buffer

void *producer(void *arg) {
    int item;
    for (int i = 0; i < 20; i++) {  // Esegue 20 produzioni per dimostrazione
        item = rand() % 100;  // Produce un valore casuale

        // Attende che ci sia almeno uno slot vuoto
        sem_wait(&empty_slots);

        // Entra nella sezione critica
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer produced: %d\n", item);
        pthread_mutex_unlock(&mutex);

        // Segnala che c'è un nuovo elemento nel buffer
        sem_post(&filled_slots);

        sleep(1);  // Simula il tempo di produzione
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 20; i++) {  // Esegue 20 consumazioni per dimostrazione
        // Attende che ci sia almeno uno slot pieno
        sem_wait(&filled_slots);

        // Entra nella sezione critica
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer consumed: %d\n", item);
        pthread_mutex_unlock(&mutex);

        // Segnala che c'è un nuovo slot vuoto nel buffer
        sem_post(&empty_slots);

        sleep(2);  // Simula il tempo di consumazione
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Inizializza i semafori
    sem_init(&empty_slots, 0, BUFFER_SIZE); // All'inizio tutti gli slot sono vuoti
    sem_init(&filled_slots, 0, 0);          // All'inizio non ci sono elementi nel buffer

    // Crea il thread produttore
    pthread_create(&prod_thread, NULL, producer, NULL);

    // Crea il thread consumatore
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Attende la terminazione dei thread
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Distrugge il mutex e i semafori
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);

    return 0;
}
