#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


void * conta(void * arg)
{ 
  int i;
  
  for (i=0 ; i<20 ; i++)
    { printf("numero %d \n",i);
      sleep(1);
    }
  pthread_exit(0);
}



int main()
{
  pthread_t tid;
  
  if(pthread_create(&tid,NULL,conta,NULL))
  {
    printf("error pthread create \n");
    exit(1);
  }
  printf("attendo terminazione thread \n");
  
   if(pthread_join(tid,NULL))
  {
    printf("error pthread join \n");
    exit(1);
  }
  
  printf("fine thread \n");

}