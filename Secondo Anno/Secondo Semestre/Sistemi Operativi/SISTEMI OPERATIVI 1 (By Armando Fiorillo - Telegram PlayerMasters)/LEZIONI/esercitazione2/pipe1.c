#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 256

int main (void) 
{ int pid,fd[2];
  
  int nread;
  
  char line[MAXLINE];
  
  if(pipe(fd)<0) {
    perror("error pipe"); exit(1);
  }
 
  if((pid=fork()) < 0 ) {
    perror("error fork"); exit(1);
  }
  if (pid == 0)
  {
    printf("digita una stringa \n");
    scanf("%s",line);
    
    close(fd[0]);
    write(fd[1],line,strlen(line));
  }
  else
  {
    close(fd[1]);
    nread = read(fd[0],line, MAXLINE);
    line[nread] = '\0';
    printf("padre letto la stringa %s dalla pipe \n",line);
  }
  return 0;
} 