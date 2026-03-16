#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main (int argc, char * argv[]) 
{
  int valore;
  
  if (argc != 2) {
    printf("errore: richiesto un argomento \n");
    return 1;
  }
  
  valore = atoi(argv[1]);
  
  pid_t pid;
  
  printf("processo principale con pid:%d \n",getpid());
  
  if ((pid=fork())<0)
  {
    perror("fork");
    return 1;
  }
    
  if (pid == 0) 
  {
    printf("figlio con pid:%d e valore iniziale: %d \n",getpid(),valore);
    valore += 15; 
    printf("figlio con pid:%d e valore finale: %d \n",getpid(),valore);
  }
  else 
  {
    printf("padre con pid:%d e valore iniziale: %d \n",getpid(),valore);
    valore += 10; 
    printf("padre con pid:%d e valore finale: %d \n",getpid(),valore);
  }
    
   return 0;
}