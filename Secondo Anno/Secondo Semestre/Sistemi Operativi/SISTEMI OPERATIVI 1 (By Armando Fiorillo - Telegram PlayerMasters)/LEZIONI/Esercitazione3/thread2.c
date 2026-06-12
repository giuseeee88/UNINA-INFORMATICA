#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int m=10; /* Variabile globale modificata dal thread */
int  result;

void *somma(void* arg) {//Funzione che verrà eseguita dal thread
  int *n = (int *) arg;
  printf("Somma di m + n: %d \n", m + (*n));
  sleep(2); /*Aspetta due secondi prima di terminare*/
  result = 10;
  pthread_exit(&result);
}

void main(int argc, char **argv) {
  pthread_t t;
  int  *status;
  int arg[1];

  if (argc<2) {
    printf ("uso: nome_programma <valore> \n");
    exit(1);
  } 
  
  arg[0]=atoi(argv[1]); /*valore da sommare*/

  if (pthread_create(&t, NULL, somma, arg) != 0) {
    printf ("Errore nella creazione del nuovo thread\n");
    exit(1);
  }
  
  // Attendo che il thread venga terminato
  pthread_join(t, (void**) &status);
  printf ("Il thread è terminato con status %d\n", *status);
}