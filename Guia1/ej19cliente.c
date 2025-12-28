#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdbool.h>

int main()
{
	int id = getpid();
	int server_socket;
	struct sockaddr_un server_addr;

	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, "/tmp/ej19");

	printf("cliente[%d]: me estoy conectando con el servidor...\n", id);
    fflush(stdout);
	server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
    int i;
	read(server_socket,&i,sizeof(i));
    printf("soy el proceso2 y recibi el numero %d \n",i); //0
    fflush(stdout);
    i++;
    printf("soy el proceso2 y le envio al proceso1 el numero %d \n",i);//1
    fflush(stdout);
    write(server_socket,&i,sizeof(i));
    read(server_socket,&i,sizeof(i));
    printf("soy el proceso2 y recibi el numero %d \n",i); //2
    fflush(stdout);
    i++;
    printf("soy el proceso2 y le envio al proceso1 el numero %d \n",i);//3
    fflush(stdout);
    write(server_socket,&i,sizeof(i));
	close(server_socket);
	exit(0);
}