#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <sys/types.h>

// Constantes 0 / 1 para READ / WRITE
enum { READ, WRITE };
// Constantes 0/1 para Padre / Hijo
enum { PADRE_ESCRIBE , HIJO_ESCRIBE };


// Variables globales
int pipe1[2][2];  //creo dos pipes: una para que el hijo reciba y el padre envie los mensajes y otra para que el padre reciba y el hijo envie mensajes
pid_t pid_padre;
pid_t pid_hijo;
void bsend(pid_t pid_dst,int msg){

    if(pid_dst == pid_padre){

        write(pipe1[HIJO_ESCRIBE][WRITE],&msg,sizeof(msg));
    }
   
    if(pid_dst == pid_hijo){
        write(pipe1[PADRE_ESCRIBE][WRITE],&msg,sizeof(msg));
    }
     
   
       
}

int breceive(pid_t pid_src){

    int msg;
    if(pid_src == pid_padre){
        
        read(pipe1[HIJO_ESCRIBE][READ],&msg,sizeof(msg));
        
    }
    if(pid_src == pid_hijo){
        read(pipe1[PADRE_ESCRIBE][READ],&msg,sizeof(msg));
    }
    return msg;

}

void rutina_del_hijo(){
     
    close(pipe1[PADRE_ESCRIBE][WRITE]);
    close(pipe1[HIJO_ESCRIBE][READ]);
    int i = 1;
    
    while(i < 10){
        
        bsend(pid_padre,i);
        breceive(pid_hijo);
        i = i + 2;
        }
    
    close(pipe1[PADRE_ESCRIBE][READ]);
    close(pipe1[HIJO_ESCRIBE][WRITE]);
    exit(EXIT_SUCCESS);

    }






int main(int argc, char const* argv[]){

    
     //creo la tuberia
    for(int j = 0; j < 2 ; j++){
        pipe(pipe1[j]);
    }

    //el proceso actual crea un hijo
    pid_hijo = fork();
    if(pid_hijo == 0){
        //soy el hijo
       //configuro el pipe
       rutina_del_hijo();

    }

    // cierro el primer pipe del padre del lado de read
    close(pipe1[PADRE_ESCRIBE][READ]);
    //cierro el segundo pipe del padre del lado de write
    close(pipe1[HIJO_ESCRIBE][WRITE]);
    
    if(pid_hijo!= -1 && pid_hijo != 0){
      
       
        int i = 0;
        int j;
        while(i < 10 ){
         printf("le envie a mi hijo %d",i);
        bsend(pid_hijo,i);
        j = breceive(pid_padre);
        printf("recibi el %d",j);
        i = i + 2;
        }

    
    }
    close(pipe1[PADRE_ESCRIBE][WRITE]);
    close(pipe1[HIJO_ESCRIBE][READ]);
    exit(EXIT_SUCCESS);


}



