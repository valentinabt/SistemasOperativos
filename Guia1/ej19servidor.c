#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdbool.h>

int crear_socket_de_servidor(const char *path)
{
    int server_socket;
    struct sockaddr_un server_addr;
    unsigned int slen = sizeof(server_addr);

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, path);
    unlink(server_addr.sun_path);  //se elimina el archivo anterior del socket si lo hubiera

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (bind(server_socket, (struct sockaddr *)&server_addr, slen) == -1) //asigna un nombre al socket
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, 1) == -1) //empieza a esperar conexiones
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    return server_socket;
}

int aceptar_socket_de_cliente(int server_socket)
{
    struct sockaddr_un client_addr;
    unsigned int clen = sizeof(client_addr);
    int client_socket =
        accept(server_socket, (struct sockaddr *)&client_addr, &clen);
    if (client_socket == -1)
    {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    return client_socket;
}


int main(){
    int server_socket = crear_socket_de_servidor("/tmp/ej19");
    
        int client_socket = aceptar_socket_de_cliente(server_socket);
        int i = 0;
        printf("soy el proceso1 y le envie al proceso 2 el numero %d \n",i);//0
        fflush(stdout);
        write(client_socket,&i ,sizeof(i));
        
        read(client_socket, &i,sizeof(i));
        printf("soy el proceso1 y recibi delproceso 2 el numero %d \n",i);//1
        fflush(stdout);
        i++;
        printf("soy el proceso1 y le envie al proceso 2 el numero %d \n",i);//2
        fflush(stdout);
        write(client_socket,&i ,sizeof(i));
        read(client_socket,&i,sizeof(i));
        printf("soy el proceso1 y recibi delproceso 2 el numero %d \n",i);//3
        fflush(stdout);
        printf("chauchi");
        fflush(stdout);
        exit(0);

}