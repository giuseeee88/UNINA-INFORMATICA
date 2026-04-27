#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_LETTORI 5   // Numero di lettori
#define NUM_SCRITTORI 2 // Numero di scrittori
#define NUM_ITERAZIONI 5 // Numero di iterazioni per ciascun thread (lettore o scrittore)

pthread_mutex_t mutex;      // Mutex per proteggere l'accesso al contatore read_count
pthread_mutex_t rw_mutex;   // Mutex per garantire l'accesso esclusivo da parte degli scrittori
int read_count = 0;         // Contatore dei lettori attivi
int shared_data = 0;        // Risorsa condivisa (dato che viene letta/scritta)

// Funzione lettore
void* lettore(void* arg) {
    int id = *((int*)arg);  // Otteniamo l'ID del lettore
    for (int i = 0; i < NUM_ITERAZIONI; i++) {
        // Acquisisce il mutex per proteggere read_count
        pthread_mutex_lock(&mutex);
        
        // Incrementa il numero di lettori attivi
        read_count++;
        
        // Se è il primo lettore, acquisisce rw_mutex per evitare che gli scrittori accedano
        if (read_count == 1) {
            pthread_mutex_lock(&rw_mutex);  // Impedisce agli scrittori di accedere
        }

        // Rilascia il mutex per permettere ad altri lettori di entrare
        pthread_mutex_unlock(&mutex);

        // Lettura della risorsa condivisa
        printf("Lettore %d legge la risorsa: %d\n", id, shared_data);
        
        // Simula un po' di tempo per la lettura
        sleep(rand() % 2 + 1);

        // Acquisisce il mutex per aggiornare read_count
        pthread_mutex_lock(&mutex);

        // Decrementa il numero di lettori attivi
        read_count--;
        
        // Se è l'ultimo lettore, rilascia rw_mutex per permettere agli scrittori di accedere
        if (read_count == 0) {
            pthread_mutex_unlock(&rw_mutex);  // Permette agli scrittori di accedere
        }

        // Rilascia il mutex
        pthread_mutex_unlock(&mutex);

        // Simula un ritardo tra le letture
        sleep(rand() % 2 + 1);
    }

    return NULL;
}

// Funzione scrittore
void* scrittore(void* arg) {
    int id = *((int*)arg);  // Otteniamo l'ID dello scrittore
    for (int i = 0; i < NUM_ITERAZIONI; i++) {
        // Acquisisce rw_mutex per avere l'accesso esclusivo alla risorsa condivisa
        pthread_mutex_lock(&rw_mutex);

        // Scrittura sulla risorsa condivisa
        shared_data++;
        printf("Scrittore %d scrive la risorsa: %d\n", id, shared_data);

        // Simula un po' di tempo per la scrittura
        sleep(rand() % 2 + 1);

        // Rilascia rw_mutex per permettere ad altri thread (lettori o scrittori) di accedere
        pthread_mutex_unlock(&rw_mutex);

        // Simula un ritardo tra le scritture
        sleep(rand() % 2 + 1);
    }

    return NULL;
}

int main() {
    pthread_t lettori[NUM_LETTORI];  // Array di thread lettori
    pthread_t scrittori[NUM_SCRITTORI];  // Array di thread scrittori

    int i;
    int lettore_ids[NUM_LETTORI];
    int scrittore_ids[NUM_SCRITTORI];

    // Inizializza i mutex
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&rw_mutex, NULL);

    // Crea i thread lettori
    for (i = 0; i < NUM_LETTORI; i++) {
        lettore_ids[i] = i + 1;  // Assegna un ID al lettore
        pthread_create(&lettori[i], NULL, lettore, &lettore_ids[i]);
    }

    // Crea i thread scrittori
    for (i = 0; i < NUM_SCRITTORI; i++) {
        scrittore_ids[i] = i + 1;  // Assegna un ID allo scrittore
        pthread_create(&scrittori[i], NULL, scrittore, &scrittore_ids[i]);
    }

    // Aspetta che i thread finiscano
    for (i = 0; i < NUM_LETTORI; i++) {
        pthread_join(lettori[i], NULL);
    }

    for (i = 0; i < NUM_SCRITTORI; i++) {
        pthread_join(scrittori[i], NULL);
    }

    // Distrugge i mutex
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&rw_mutex);

    return 0;
}
