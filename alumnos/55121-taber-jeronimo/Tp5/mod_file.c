#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "mod.h"
int conf(char *file) {
int fd,leido,port;
char ptr[1024];
 fd = open(file, O_RDONLY);      
 if(fd == -1){//si no se puede abir el archivo muesta error
                perror("open");
                return 0;
        }
       leido  = read(fd, ptr, 1024);
	
	char enter[5] = " ";
	char equal[5] = "=";
        char *tok = strtok(ptr, enter);
 	char *last_tok = NULL;
        char *tok2 = strtok(tok, equal);
        while (tok2){
                last_tok = tok2;
                tok2 = strtok(NULL, equal);
        }
	port=atoi(last_tok);
	
close(fd);
	return port;

}
