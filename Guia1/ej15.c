#include <stdio.h>    // printf()
#include <stdlib.h>   // exit()
#include <unistd.h>   // fork() pipe() execlp() dup2() close()
#include <sys/wait.h> // wait()
#include <sys/types.h>
// Constantes 0 / 1 para READ / WRITE
enum { READ, WRITE };

int pipe_c[2];
// Debe ejecutar "ls -al"
void ejecutar_hijo_1(int pipe_fd[]) {
    close(pipe_fd[READ]);
   printf("soy ls!");

   //conecto el stdout con el pipe nuevo
    dup2(pipe_c[WRITE],1);

    //argumentos para execvp: la ruta del programa que queremos ejecutar, el argumento -a y NULL al final.
    char *args[] = {"ls", "-al", NULL};  

    close(pipe_c[WRITE]); //lo cierro pues lo va a usar ls, no este proceso.
    //va a reemplazar la ejecucion de este programa por el primer agumento de execvp.
    //ls va a heredar la tabla de file descriptors, es decir, va a enviar su salida al stin del wc!!!!!!!!!!
    execvp(args[0],args);
    //si todo sale bien, se ejecuta ls y termina. Y el hijo se muere

   
}

// Debe ejecutar "wc -l"
void ejecutar_hijo_2(int pipe_fd[]) {
    close(pipe_fd[WRITE]);
    printf("en wc !!!");
    //conecto el stdin al pipe donde recibo el input
    dup2(pipe_c[READ],0);
    //ahora el input de wc sera el output de ls
    close(pipe_c[READ]);
    char *args[] = {"wc", "-l", NULL};  
    execvp(args[0],args);
   
}

int main(int argc, char const* argv[]) {
  //Proceso principal: shell
    
    pipe(pipe_c);
    
  pid_t ls_pid = fork();
  if(ls_pid == 0){
     
    ejecutar_hijo_1(pipe_c);
  } 
  
  
  pid_t wc_pid = fork();
  if(wc_pid == 0){
    printf("por ejecutar wc");
    ejecutar_hijo_2(pipe_c);
  }
  
  close(pipe_c[WRITE]);
  close(pipe_c[READ]);
  
  return 0;
}