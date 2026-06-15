#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int counter = 0;                 // variabile condivisa
sem_t sem;                       // semaforo usato come mutex

void* thread_func(void* arg) {
    for (int i = 0; i < 100000; i++) {
        // Entra in sezione critica aspettando sul semaforo
        sem_wait(&sem);
        
        counter++;                   // accesso alla variabile condivisa
        
        // Esce dalla sezione critica incrementando il semaforo
        sem_post(&sem);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Inizializza il semaforo: 
    // - secondo parametro 0: semaforo condiviso tra thread dello stesso processo
    // - terzo parametro 1: valore iniziale (agisce come un mutex binario)
    sem_init(&sem, 0, 1);

    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Distrugge il semaforo
    sem_destroy(&sem);

    printf("Counter finale (con semafori): %d\n", counter);
    return 0;
}
