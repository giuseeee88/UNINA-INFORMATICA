#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    int pipefd[2];

    // TODO 1: creare la pipe
    // if (...) { perror("pipe"); exit(1); }

    pid_t pid = fork();

    // TODO 2: controllare errore fork

    if (pid == 0) {
        // FIGLIO

        // TODO 3: chiudere l'estremità non usata

        int a, b;

        // TODO 4: leggere a dalla pipe
        // TODO 5: leggere b dalla pipe

        int somma = a + b;
        printf("Figlio: %d + %d = %d\n", a, b, somma);

        // TODO 6: chiudere il descrittore rimasto aperto
    } else {
        // PADRE

        // TODO 7: chiudere l'estremità non usata

        int a = 12;
        int b = 30;

        // TODO 8: scrivere a nella pipe
        // TODO 9: scrivere b nella pipe

        // TODO 10: chiudere il descrittore rimasto aperto
    }

    return 0;
}