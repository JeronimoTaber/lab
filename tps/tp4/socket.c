#include <sys/types.h>//para socket
#include<sys/socket.h>//para socket
#include <unistd.h> //para write  y read
#include <stdio.h>
#include <errno.h>//para perror
#include <netinet/in.h> //para procrem
#include <arpa/inet.h>
#include <stdlib.h>
#include "mod.h"
#include <string.h>
int main(int argc, char ** argv){
	int numpage,fd,leido,conectado,opt,port;
	char buff[1000],*addr,*word,*ip,*url=NULL,*pagec=NULL,str[2000];
	struct sockaddr_in procrem={};
	fd = socket(AF_INET,SOCK_STREAM,0);//AF_INET(es ipv4),SOCK_STREAM(protocolo tcp)
//	url = (char *) malloc(sizeof(char));	
	
	if(fd < 0){
		perror("socket");
		return-1;
	}
	getopt(argc, argv ,"u:");
	addr = optarg;
	printf("%s \n", addr);

	getopt(argc, argv,"t:");
	word = optarg;
        printf("%s \n", word);
        
	getopt(argc, argv,"i:");
	ip = optarg;
	printf("%s \n", ip);
	
	getopt(argc, argv,"p:");
        port = atoi(optarg);
        printf("%d \n", port);
	
	/*url = urlm(addr);
	
        printf("%s \n", url);
	
	pagec = pagem(addr,url); 
	printf("%s \n", pagec);
     */
//	free(url);

strcpy (str,addr);
strcat (str," ");
strcat (str,word);
printf("%s \n",str);
        numpage = 0;
        for(int x=0; str[x]; x++) {
        if(str[x] != ' ') {
        numpage ++;
         }
        }
	numpage++;
printf("%d \n",numpage);
	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(port);//htons evita el problema de que de vuelta el numero
	inet_pton(AF_INET, ip, &procrem.sin_addr);//lo transfora en binario antes de madarlo
	conectado = connect(fd,(struct sockaddr *)&procrem/* &procrem se le agrega lo otro, porque es generico y se le agrega un puntero para eliminar la warning*/, sizeof procrem);//el file descriptor (fd) se conecta con la ip (192.168.1.52)dada por sin.addr en el puesto (25) dado por sin_port	
	        if(conectado < 0){
                perror("connect");
                return-1;
        }
	
	write(fd,str,numpage);//si usamos el puerto 80 (apache) se escribe en pantalla una pagina pedida a apache por GET/
	leido = read(fd, buff, sizeof buff);
        if(leido < 0){
                perror("read");
                return-1;
        }
	write(1,buff,leido);
	return 0;
}
