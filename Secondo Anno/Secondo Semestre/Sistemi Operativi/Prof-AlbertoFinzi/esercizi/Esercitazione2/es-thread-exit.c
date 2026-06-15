#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* worker(void* arg) {
    int x = *(int*)arg;

    int* risultato = malloc(sizeof(int));
    *risultato = x * x;

    printf("Thread: calcolo %d^2 = %d\n", x, *risultato);

    pthread_exit(risultato);
}

int main() {
    pthread_t t;
    int valore = 5;

    void* res;

    pthread_create(&t, NULL, worker, &valore);

    pthread_join(t, &res);

    int risultato = *(int*)res;
    printf("Main: risultato ricevuto = %d\n", risultato);

    free(res);

    return 0;
}