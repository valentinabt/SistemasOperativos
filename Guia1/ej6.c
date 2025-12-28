#include <stdio.h>   // printf()
#include <stdlib.h>  // exit()
#include <unistd.h>  // fork() pipe() write() read()
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "mini-shell-parser.c"

static int system_2(char ***program_with_parameters){
    
    pid_t child = fork();
    if(child == 0){
        execvp(program_with_parameters[0][0],program_with_parameters[0]);
        exit(EXIT_FAILURE);
    }
    else {
        int status;
        waitpid(child,&status,0);

        if(WIFEXITED(status)){
         return(WEXITSTATUS(status));
        } else {
            return -1;
    }

}
}

int main(int argc, char const* argv[]){

 if (argc < 2)
	{
		printf("El programa recibe como parametro de entrada un string con la linea de comandos a ejecutar. \n");
		printf("Por ejemplo ./mini-shell 'ls -a | grep anillo'\n");
		return 0;
	}
	int programs_count = argc;
	char ***programs_with_parameters = parse_input(argv, &programs_count);

	printf("status: %d\n", system_2(programs_with_parameters));

    exit(EXIT_SUCCESS);



}