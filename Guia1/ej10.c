#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


int main(){

pid_t pid_julieta = fork();

    if(pid_julieta==0){
        printf("soy Julieta \n");
        sleep(1);
        pid_t pid_jennifer = fork();
        if(pid_jennifer==0){
            printf("soy Jennifer \n");
            sleep(1);
        }

     }
     else{
        printf("soy juan \n");
        sleep(1);
        wait(NULL);
        //ya se murio julieta
        pid_t pid_jorge = fork();
        if(pid_jorge ==0){
            printf("soy Jorge \n");
            sleep(1);
        }
     }








}