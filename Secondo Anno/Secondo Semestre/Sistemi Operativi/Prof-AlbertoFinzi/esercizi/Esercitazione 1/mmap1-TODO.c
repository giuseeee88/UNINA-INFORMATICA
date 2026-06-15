#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int somma;
} SharedData;

int main() {
    // TODO 1: creare una zona condivisa con mmap
    // SharedData *data = ...

    // TODO 2: controllare errore mmap

    pid_t pid = fork();

    // TODO 3: controllare errore fork

    if (pid == 0) {
        // FIGLIO

        // opzionale: piccola attesa per sicurezza
        sleep(1);

        // TODO 4: leggere data->a e data->b e calcolare la somma
        // TODO 5: salvare il risultato in data->somma

        printf("Figlio: %d + %d = %d\n", data->a, data->b, data->somma);
    } else {
        // PADRE

        // TODO 6: scrivere i due numeri nella zona condivisa
        // data->a = ...
        // data->b = ...

        wait(NULL);

        printf("Padre legge risultato: %d\n", data->somma);
    }

    // TODO 7: chiamare munmap

    return 0;
}