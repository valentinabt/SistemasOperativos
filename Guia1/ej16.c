#include <stdio.h>    // printf()
#include <stdlib.h>   // exit()
#include <unistd.h>   // fork() pipe() execlp() dup2() close()
#include <sys/wait.h> // wait()
#include <sys/types.h>
// Constantes 0 / 1 para READ / WRITE
enum { READ, WRITE };

void rutina_hijo1(int (*pipes)[2]){
    close(pipes[0][WRITE]);
    close(pipes[0][READ]);
    close(pipes[1][WRITE]);
    close(pipes[2][READ]);

    int i;
    while(read(pipes[1][READ],&i,sizeof(i))>0 && i <50){
        i++;
        write(pipes[2][WRITE],&i,sizeof(i));


    }
    printf("soy el hijo1 y mori con i = %d",i);
    exit(EXIT_SUCCESS);




}

void rutina_hijo2(int (*pipes)[2]){
    close(pipes[0][READ]);
    close(pipes[1][READ]);
    close(pipes[1][WRITE]);
    close(pipes[2][WRITE]);

    int i;
    while(read(pipes[2][READ],&i,sizeof(i))>0 && i <50){
        i++;
        write(pipes[0][WRITE],&i,sizeof(i));


    }
    printf("soy el hijo2 y mori con i = %d",i);
    exit(EXIT_SUCCESS);




}

int main(){

int (*pipes)[2] = malloc(sizeof(*pipes) * 3);

for(int i = 0; i < 3; i++){
    pipe(pipes[i]);
}
pid_t hijo1 = fork();

if(hijo1==0){
    rutina_hijo1(pipes);
}
else{
    pid_t hijo2 = fork();
    if(hijo2==0){
        rutina_hijo2(pipes);
    }
    else{
        close(pipes[0][WRITE]);
        close(pipes[1][READ]);
        close(pipes[2][WRITE]);
        close(pipes[2][READ]);

        int i = 0;
        write(pipes[1][WRITE],&i,sizeof(i));
        while(read(pipes[0][READ],&i,sizeof(i))>0 && i < 50){
            i++;
            write(pipes[1][WRITE],&i,sizeof(i));

        }
        printf("soy el padre y mori con i = %d",i);
        exit(EXIT_SUCCESS);


    }
}





}