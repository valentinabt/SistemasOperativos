#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <sys/types.h>

// Constantes 0 / 1 para READ / WRITE
enum { READ, WRITE };
// Constantes 0/1/2 para Padre / Hijo1 / Hijo2
enum { padre_tohijo1 , hijo1_tohijo2 , hijo2_toPadre};


// Variables globales
int pipe1[3][2];
pid_t pid_padre;
pid_t pid_hijo1;
pid_t pid_hijo2;
void bsend(pid_t pid_dst,int msg){

    if(pid_dst == pid_padre){

        write(pipe1[hijo2_toPadre][WRITE],&msg,sizeof(msg));
    }
   
    if(pid_dst == pid_hijo1){
        write(pipe1[padre_tohijo1][WRITE],&msg,sizeof(msg));
    }
    if(pid_dst == pid_hijo2){
        write(pipe1[hijo1_tohijo2][WRITE],&msg,sizeof(msg));
    }
     
   
       
}

int breceive(pid_t pid_src){

    int msg;
    if(pid_src == pid_hijo2){
        
        read(pipe1[hijo2_toPadre][READ],&msg,sizeof(msg));
        
    }
    if(pid_src == pid_padre){
        read(pipe1[padre_tohijo1][READ],&msg,sizeof(msg));
    }

    if(pid_src == pid_hijo1){
        read(pipe1[hijo1_tohijo2][READ],&msg,sizeof(msg));
    }


    return msg;

}

void rutina_del_hijo1(){
     
    close(pipe1[padre_tohijo1][WRITE]);
    close(pipe1[hijo1_tohijo2][READ]);
    close(pipe1[hijo2_toPadre][READ]);
    close(pipe1[hijo2_toPadre][WRITE]);

    int k = 0;
    while(k+1 < 50){
        
        k = breceive(pid_padre);
        printf("soy el hijo 1 y recibi %d \n",k);
        bsend(pid_hijo2,k+1);
        printf("soy el hijo 1 y le envie al hijo 2 %d \n",k+1);
        
        k++;
        }
    
    close(pipe1[padre_tohijo1][READ]);
    close(pipe1[hijo1_tohijo2][WRITE]);
    exit(EXIT_SUCCESS);

    }

void rutina_del_hijo2(){
     
    close(pipe1[padre_tohijo1][WRITE]);
    close(pipe1[padre_tohijo1][READ]);
    close(pipe1[hijo1_tohijo2][WRITE]);
    close(pipe1[hijo2_toPadre][READ]);

    int k = 0;
    while(k+1 < 50){
        
        k = breceive(pid_hijo1) ;
        printf("soy el hijo 2 y recibi %d \n",k);
        
        bsend(pid_padre,k+1);

        printf("soy el hijo 2 y le envie a padre  %d \n",k+1);
        
        k++;
        }
    
    close(pipe1[hijo2_toPadre][WRITE]);
    close(pipe1[hijo1_tohijo2][READ]);
    exit(EXIT_SUCCESS);

    }


int main(int argc, char const* argv[]){

    
     //creo la tuberia
    for(int j = 0; j < 3 ; j++){
        pipe(pipe1[j]);
    }

    //el proceso actual crea el primer hijo
    pid_hijo1 = fork();
    if(pid_hijo1 == 0){
        //soy el hijo
       //configuro el pipe
       rutina_del_hijo1();

    }
    
    //-----------------

    pid_hijo2 = fork();
    if(pid_hijo2 == 0){
        //soy el hijo
       //configuro el pipe
       rutina_del_hijo2();

    }
   
    
    
    if(pid_hijo1!= -1 && pid_hijo1 != 0 && pid_hijo2!= -1 && pid_hijo2 != 0){
      
       
    // cierro el primer pipe del padre del lado de read
    close(pipe1[padre_tohijo1][READ]);
    //cierro el pipe del hijo 1 al hijo 2
    close(pipe1[hijo1_tohijo2][WRITE]);
    close(pipe1[hijo1_tohijo2][READ]);

     //cierro el segundo pipe del padre del lado de write
    close(pipe1[hijo2_toPadre][WRITE]);
    
        int i = 0;
        int j;
        while(i < 50 ){
         
        bsend(pid_hijo1,i);
        printf("le envie a mi hijo1 %d \n",i);
        j = breceive(pid_hijo2);
        printf("recibi de hijo 2 el %d \n",j);
        i = j+1;
        }

    
    }
    close(pipe1[padre_tohijo1][WRITE]);
    close(pipe1[hijo2_toPadre][READ]);
    exit(EXIT_SUCCESS);


}



