#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <sys/types.h>
#include <sys/wait.h>

int main(){
     printf("hola! soy Abraham \n");
    pid_t pid_homero = fork();

    if(pid_homero == 0){
        //soy homero
        pid_t pid_bart;
        pid_t pid_lisa;
        pid_t pid_maggie;
        printf("hola! soy homero \n ");
        pid_lisa = fork();
        if(pid_lisa == 0){

            printf("hola! soy lisa \n");
            exit(EXIT_SUCCESS);

        }
        else{
            pid_bart = fork();
            if(pid_bart == 0){
                printf("hola! soy Bart \n");
                exit(EXIT_SUCCESS);

            }
            else{
                 pid_maggie = fork();
                if(pid_maggie== 0){
                    printf("hola! soy maggie \n");
                    exit(EXIT_SUCCESS);
                }
            }
        }
        //waitpid(pid_lisa);
        //waitpid(pid_bart);
        //waitpid(pid_maggie);
         exit(EXIT_SUCCESS);
    }
    //waitpid(pid_homero);
    exit(EXIT_SUCCESS);


}