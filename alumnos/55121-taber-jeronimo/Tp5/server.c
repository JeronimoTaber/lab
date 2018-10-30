#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <pthread.h>
#include <string.h>
#include "mod.h"
//int g = 0;
pthread_mutex_t mutex;
void *servicio (void* connfd){
	
	user(connfd);
	pthread_exit(NULL);
	//return 0;
}
char *file;
int main(int argc,char **argv){
	pthread_t tid;
	pthread_mutex_init(&mutex,NULL); 
	pthread_mutex_lock(&mutex);
	char *port=NULL;//,*file=NULL;
	int fd,connfd,reuse,portnum,i=0;
	struct sockaddr_in procrem={};
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd < 0 ){
		perror ("socket");
		return -1;
	}
	reuse = 1;
int c = getopt (argc, argv, "f::");	
if(( c != (-1))) { 
	
	file = argv[2];
	printf ("%s \n",file);
	}
else{
	
	file = "tp5.conf";
	} 	
	
	portnum = conf(file);
	printf("port: %d \n",portnum);
	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(portnum);
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&reuse, sizeof reuse);
	if (bind(fd,(struct sockaddr *)&procrem, sizeof procrem) < 0 ) {
		perror ("bind");
                return -1;
        }

	listen(fd, 100);
	while ( (connfd = accept(fd,NULL, 0)) > 0 ){
	//	i++;
		
		pthread_create(&tid, NULL, servicio,(void *)(intptr_t) connfd);
	pthread_mutex_lock(&mutex);

//		pthread_detach(tid);
//		pthread_join(tid,NULL);
//		fd=0;
	}
	
	//close(connfd);
	return 0;
}	
