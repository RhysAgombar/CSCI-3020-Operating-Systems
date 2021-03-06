#define _XOPEN_SOURCE 600

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
  int status;
  pid_t pid;
  pid=fork();
  if(pid == 0){
    execlp("./process",(char*) NULL);
  }else if(pid<0){
    // fork failed to fork
    fprintf(stderr,"Fork failed.\n");
    status = -1;
  }else {
    sleep(5);
    kill(pid,SIGINT);
    waitpid(pid,&status,0);
  }
  return 0;
}
