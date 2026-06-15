#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int somma;
} SharedData;

int main() {
    // TODO 1: aprire/creare il file shared.bin
    int fd;

    // TODO 2: usare ftruncate per dare al file la dimensione giusta

    // TODO 3: fare mmap del file
    SharedData *data;

    // TODO 4: controllare errore mmap

    pid_t pid = fork();

    // TODO 5: controllare errore fork

    if (pid == 0) {
        sleep(1);

        // TODO 6: calcolare la somma e salvarla
        printf("Figlio: %d + %d = %d\n", data->a, data->b, data->somma);
    } else {
        // TODO 7: inizializzare a e b
        wait(NULL);
        printf("Padre legge risultato: %d\n", data->somma);
    }

    // TODO 8: munmap
    // TODO 9: close(fd)

    return 0;
}