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
char *dir(char *file) {
int fda,leido,port,sizedir,size;
char ptr[1024],destino[1000]="",*pass=NULL;
//void *conf(void *file) {
//return 0;
 fda = open(file, O_RDONLY);      
 if(fda == -1){//si no se puede abir el archivo muesta error
                perror("open");
                return 0;
        }
       leido  = read(fda, ptr, 1024);
	        struct stat fileStat;
        fstat(fda,&fileStat);
	
        size = fileStat.st_size - 17;
	strncpy(destino,&ptr[16],size);
	pass = destino;
	close(fda);
	return pass;

}
