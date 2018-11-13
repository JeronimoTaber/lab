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
void *child(void *connfd) {
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
}
