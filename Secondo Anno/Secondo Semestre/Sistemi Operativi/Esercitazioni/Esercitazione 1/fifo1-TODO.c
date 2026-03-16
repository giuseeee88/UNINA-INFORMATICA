#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    const char *nome_fifo = "canale_fifo";

    // TODO 1: creare la FIFO con mkfifo
    // gestire eventualmente il caso di errore

    pid_t pid = fork();

    // TODO 2: controllare errore fork

    if (pid == 0) {
        // FIGLIO

        // TODO 3: aprire la FIFO in lettura

        int a, b;

        // TODO 4: leggere a
        // TODO 5: leggere b

        int somma = a + b;
        printf("Figlio: %d + %d = %d\n", a, b, somma);

        // TODO 6: chiudere la FIFO
    } else {
        // PADRE

        // TODO 7: aprire la FIFO in scrittura

        int a = 7;
        int b = 18;

        // TODO 8: scrivere a
        // TODO 9: scrivere b

        // TODO 10: chiudere la FIFO
    }

    return 0;
}