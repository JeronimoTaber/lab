#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <string.h>
#include "mod.h"
int fileopen();
//void child(int connfd);
int main(){
	char buff[1000],dir[1000],slash[2]="/",path[1000],buffer[10000];
	int fd, fdcliente, leido, conectado, connfd, pid;
	struct sockaddr_in procrem={};
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd < 0 ){
		perror ("socket");
		return -1;
	}

	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(8080);
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	int a=1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
	if (bind(fd,(struct sockaddr *)&procrem, sizeof procrem) < 0 ) {
		perror ("bind");
                return -1;
        }

	listen(fd, 5);
	signal(SIGCHLD,SIG_IGN ); //para sacar procesos terminados de la PCB ...
	while ( (connfd = accept(fd,NULL, 0)) > 0 ){
		pid = fork();
		//hijo
		if ( pid == 0 ) {
			child(connfd);
		return 0;
		}
		close(connfd);
	}
	return 0;
}


int fileopen (){//abre el archivo ingrasado
	int fd = open("/proc/meminfo" , O_RDONLY);	
	if(fd == -1){//si no se puede abir el archivo muesta error
		perror("open");

	}
	return fd;//devuelve archivo
}	
/*

void child (int connfd){
	char buff[1000],dir[1000],slash[2]="/",path[1000],buffer[10000];
	int fdcliente, leido, conectado, pid;
	leido = read (connfd,buff ,sizeof buff);
        char enter[5] = "/";
                        if (sscanf(buff, "GET /mem/info/%s", dir) == 1){}
                        else{
                                char error404[1000] = "HTTP/1.0 404 Not Found \n";
                                write (connfd,error404 ,24);
                                return;
                        }
                        sscanf(buff, "GET /mem/info/%s", dir);  
                        int len = strlen(dir);
                        write (1 ,dir,len);
                        int fd = fileopen();//llama a funcion fileopen
                        if(fd == -1){//si no se puede abir el archivo muesta error
                                char error404[1000] = "HTTP/1.0 404 Not Found \n";
                                write (connfd,error404 ,24);
                                perror("open");
                                close(fd);
                                return;
                        }
        leido = read(fd, buffer, sizeof buffer);
        if(leido < 0){
                perror("read");
                return;
        }       
                char * tok, *p;
                int find=0;
                tok = strtok (buffer,"\n");
                while (tok != NULL){
                        p = strstr (tok,dir);
                        if(p)
                        {
                                find ++;
                                if(find == 1){
                                write(connfd,"HTTP/1.0 200 OK\n",16);
                                }
                                int leng = strlen(tok);
                                printf ("%s\n",tok);
                                write(connfd,"\n",1);
                                write(connfd,tok,leng);

                        }
                        tok = strtok (NULL, "\n");
                }
                if (find == 0){
                                char error404[1000] = "HTTP/1.0 404 Not Found \n";
                                write (connfd,error404 ,24);
                                close(fd);
                                return;
                }

}*/
