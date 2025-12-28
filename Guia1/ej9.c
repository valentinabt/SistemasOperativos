#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


pid_t pid_child;

void handler_pong(){

    printf("pong \n");
    fflush(stdout);
  
}


void rutina_hijo(){
   
    signal(SIGUSR1,&handler_pong);
   
    while(1){
        
    }

}

int rutina_padre(){
     
    for(int i = 0; i < 3; i++){
        printf("ping \n");
        fflush(stdout);
        kill(pid_child,SIGUSR1);
        sleep(1);
    }
    kill(pid_child,SIGTERM);
    waitpid(pid_child,NULL,0);
    exit(EXIT_SUCCESS);
}

int main(){

  pid_child = fork();
  
  
  if(pid_child==0){
    rutina_hijo();
  }
  else{
    rutina_padre();
  }

}