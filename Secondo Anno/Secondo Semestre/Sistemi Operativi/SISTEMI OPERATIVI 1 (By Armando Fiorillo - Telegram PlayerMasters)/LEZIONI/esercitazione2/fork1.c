#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (void) 
{
  pid_t pid;
  
  printf("prima di fork, pid:%d ppid:%d \n",getpid(),getppid());
  
  if ((pid=fork())<0)
    {
    printf(" errore di fork \n");
    return 1;
    }
    
    printf("dopo fork, pid:%d ppid:%d \n",getpid(),getppid());
    
   return 0;
}