#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    struct winsize w;

    // Controllo argomenti
    if (argc != 3) {
        printf("Uso: %s <righe> <colonne>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    // TODO 1:
    // usare ioctl() per leggere
    // la dimensione del terminale
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl");
        return 1;
    }

    printf("Terminale: %d righe x %d colonne\n",
           w.ws_row, w.ws_col);

    // TODO 2:
    // verificare se la matrice entra nel terminale
    //
    // Suggerimento:
    // ogni numero occupa circa 4 caratteri
    if (rows > w.ws_row || (cols * 4) > w.ws_col) {
        // TODO 3:
        // se il terminale è troppo piccolo:
        // - stampare messaggio
        // - chiedere resize
        // - attendere ENTER
        // - terminare
        printf("Terminale troppo piccolo per la matrice %dx%d\n", rows, cols);
        printf("Ridimensionare il terminale e premere ENTER per uscire...\n");
        getchar();
        return 1;
    }

    // TODO 4:
    // stampare una matrice rows x cols
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", i * cols + j);
        }
        printf("\n");
    }

    return 0;
}