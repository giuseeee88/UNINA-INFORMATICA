#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5  // Numero di filosofi
#define M 10 // Numero di cicli di pensare e mangiare per ciascun filosofo

typedef enum { THINKING, HUNGRY, EATING } State;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond[N];
State stato[N];

// Funzione per verificare se un filosofo può mangiare
void controlla(int id) {
    int sinistra = (id + N - 1) % N;
    int destra = (id + 1) % N;
    if (stato[id] == HUNGRY && stato[sinistra] != EATING && stato[destra] != EATING) {
        stato[id] = EATING;
        pthread_cond_signal(&cond[id]);
    }
}

// Funzione che rappresenta l'azione di prendere le bacchette
void prendi_bacchette(int id) {
    pthread_mutex_lock(&mutex);
    stato[id] = HUNGRY;
    printf("Filosofo %d è affamato.\n", id);
    controlla(id);  // Controlla se può iniziare a mangiare
    while (stato[id] != EATING) {
        pthread_cond_wait(&cond[id], &mutex);  // Attende finché non può mangiare
    }
    pthread_mutex_unlock(&mutex);
}

// Funzione che rappresenta l'azione di rilasciare le bacchette
void rilascia_bacchette(int id) {
    pthread_mutex_lock(&mutex);
    stato[id] = THINKING;
    printf("Filosofo %d ha smesso di mangiare e torna a pensare.\n", id);
    // Controlla se i vicini possono ora mangiare
    controlla((id + N - 1) % N);
    controlla((id + 1) % N);
    pthread_mutex_unlock(&mutex);
}

// Funzione che rappresenta il comportamento di ogni filosofo
void *filosofo(void *arg) {
    int id = *(int *)arg;

    for (int i = 0; i < M; i++) {
        // Pensare
        printf("Filosofo %d sta pensando. Ciclo %d di %d.\n", id, i + 1, M);
        usleep(rand() % 500000);  // Simula il pensiero

        // Tentativo di prendere le bacchette
        prendi_bacchette(id);

        // Mangiare
        printf("Filosofo %d sta mangiando. Ciclo %d di %d.\n", id, i + 1, M);
        usleep(rand() % 500000);  // Simula il mangiare

        // Rilasciare le bacchette
        rilascia_bacchette(id);
    }

    printf("Filosofo %d ha completato tutti i suoi cicli.\n", id);
    return NULL;
}

int main() {
    pthread_t filosofi[N];
    int id[N];

    // Inizializza le variabili di condizione per ogni filosofo
    for (int i = 0; i < N; i++) {
        pthread_cond_init(&cond[i], NULL);
        stato[i] = THINKING;  // All'inizio, tutti i filosofi stanno pensando
    }

    // Crea i thread per ogni filosofo
    for (int i = 0; i < N; i++) {
        id[i] = i;
        if (pthread_create(&filosofi[i], NULL, filosofo, &id[i]) != 0) {
            perror("Errore nella creazione del thread");
            exit(1);
        }
    }

    // Attendi che i thread dei filosofi finiscano
    for (int i = 0; i < N; i++) {
        pthread_join(filosofi[i], NULL);
    }

    // Distruggi le variabili di condizione
    for (int i = 0; i < N; i++) {
        pthread_cond_destroy(&cond[i]);
    }

    return 0;
}
