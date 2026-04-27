#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_STUDENTI 4
#define NUM_PROF 2

int stampante_occupata = 0;
int prof_in_attesa = 0;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv_studenti = PTHREAD_COND_INITIALIZER;
pthread_cond_t cv_prof = PTHREAD_COND_INITIALIZER;

void usa_stampante(const char* tipo, int id) {
    printf("[%s %d] stampa...\n", tipo, id);
    printf("[%s %d] fine\n", tipo, id);
}

void* professore(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mtx);

    // TODO 1:
    // incrementare il numero di professori in attesa
    prof_in_attesa++;

    // TODO 2:
    // aspettare finché la stampante è occupata
    while (stampante_occupata) {
        pthread_cond_wait(&cv_prof, &mtx);
    }

    // TODO 3:
    // decrementare il numero di professori in attesa
    // e occupare la stampante
    prof_in_attesa--;
    stampante_occupata = 1;

    pthread_mutex_unlock(&mtx);

    usa_stampante("PROF", id);

    pthread_mutex_lock(&mtx);

    // TODO 4:
    // liberare la stampante
    stampante_occupata = 0;

    // TODO 5:
    // se ci sono professori in attesa, svegliarne uno
    // altrimenti svegliare uno studente
    if (prof_in_attesa > 0) {
        pthread_cond_signal(&cv_prof);
    } else {
        pthread_cond_signal(&cv_studenti);
    }

    pthread_mutex_unlock(&mtx);

    return NULL;
}

void* studente(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mtx);

    // TODO 6:
    // aspettare finché:
    // - la stampante è occupata
    // - oppure ci sono professori in attesa
    while (stampante_occupata || prof_in_attesa > 0) {
        pthread_cond_wait(&cv_studenti, &mtx);
    }

    // TODO 7:
    // occupare la stampante
    stampante_occupata = 1;

    pthread_mutex_unlock(&mtx);

    usa_stampante("STUD", id);

    pthread_mutex_lock(&mtx);

    // TODO 8:
    // liberare la stampante
    stampante_occupata = 0;

    // TODO 9:
    // policy di risveglio coerente con la priorità
    if (prof_in_attesa > 0) {
        pthread_cond_signal(&cv_prof);
    } else {
        pthread_cond_signal(&cv_studenti);
    }

    pthread_mutex_unlock(&mtx);

    return NULL;
}

int main() {
    pthread_t th[NUM_STUDENTI + NUM_PROF];
    int ids[NUM_STUDENTI + NUM_PROF];

    for (int i = 0; i < NUM_PROF; i++) {
        ids[i] = i;
        pthread_create(&th[i], NULL, professore, &ids[i]);
    }

    for (int i = 0; i < NUM_STUDENTI; i++) {
        ids[NUM_PROF + i] = i;
        pthread_create(&th[NUM_PROF + i], NULL, studente, &ids[NUM_PROF + i]);
    }

    for (int i = 0; i < NUM_STUDENTI + NUM_PROF; i++) {
        pthread_join(th[i], NULL);
    }

    return 0;
}