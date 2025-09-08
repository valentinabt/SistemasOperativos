#include <stdio.h>    // printf()
#include <stdlib.h>   // exit()
#include <unistd.h>   // fork() pipe() execlp() dup2() close()
#include <sys/wait.h> // wait()

// Constantes 0 / 1 para READ / WRITE
enum { READ, WRITE };

int pipe_c[2];
// Debe ejecutar "ls -al"
void ejecutar_hijo_1(int pipe_fd[]) {
    close(pipe_fd[READ]);
 

    //usar dup2!!!!!!!!!!!!!!!

    //argumentos para execvp: la ruta del programa que queremos ejecutar, el argumento -a y NULL al final.
    char *args[] = {"/bin/ls", "-l", "-a", NULL};  

    //va a reemplazar la ejecucion de este programa por el primer agumento de execvp.
    //ls va a heredar la tabla de file descriptors, es decir, va a enviar su salida al stin del wc!!!!!!!!!!
    execvp(args[0],args);
    //si todo sale bien, se ejecuta ls y termina. Y el hijo se muere

   
}

// Debe ejecutar "wc -l"
void ejecutar_hijo_2(int pipe_fd[]) {
    close(pipe_fd[WRITE]);

    exit(EXIT_SUCCESS);
}

int main(int argc, char const* argv[]) {
  //Proceso principal: shell
  
  for(int i = 0; i < 2; i++){
    pipe(pipe_c[i]);
    
  }
  
  pid_t ls_pid = fork();
  if(ls_pid == 0){

    ejecutar_hijo_1(pipe_c);
  } 
  
  pid_t wc_pid = fork();
  if(wc_pid == 0){
    ejecutar_hijo_2(pipe_c);
  }
  close(pipe_c[WRITE]);
  close(pipe_c[READ]);
  exit(EXIT_SUCCESS);
  return 0;
}