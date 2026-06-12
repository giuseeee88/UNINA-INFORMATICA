#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Struttura per passare i parametri al thread
typedef struct {
    int number;  // Numero di cui calcolare il quadrato
    int thread_id; // ID del thread
} ThreadData;

// Funzione che verrà eseguita dai thread
void* calculate_square(void* arg) {
    // Cast dell'argomento al tipo corretto
    ThreadData* data = (ThreadData*)arg;
    int result = data->number * data->number;

    // Stampa il risultato
    printf("Thread %d: Il quadrato di %d è %d\n", data->thread_id, data->number, result);

    // Termina il thread
    pthread_exit(NULL);
}

int main() {
    const int num_threads = 5; // Numero di thread da creare
    pthread_t threads[num_threads]; // Array di identificatori dei thread
    ThreadData thread_data[num_threads]; // Array di dati per i thread

    // Creazione dei thread
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].number = i + 1; // Passiamo i numeri da 1 a 5
        thread_data[i].thread_id = i; // Assegniamo un ID al thread

        // Creazione del thread
        int rc = pthread_create(&threads[i], NULL, calculate_square, (void*)&thread_data[i]);
        if (rc) {
            fprintf(stderr, "Errore nella creazione del thread: %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    // Attesa per il termine di tutti i thread
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Tutti i thread hanno completato l'esecuzione.\n");
    return 0;
}
