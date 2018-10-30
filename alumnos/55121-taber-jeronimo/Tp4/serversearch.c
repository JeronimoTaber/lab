#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mod.h"
int portselect(int argc, char ** argv);
int main(int argc, char ** argv){
	int fd,fdcliente,leido,conectado,connfd,pid,port,report,numpage;
	char buff[1000],pegado[1000],enter[2]="\n",pase[1000],*addr,*nom,*url,letter[200],*pagec,search[2000],con[2000],can[2000], str[100] = "";
	port = portselect(argc, argv);	
	report = 1;	
	printf("%d atoi\n",port);
	struct sockaddr_in procrem={};
	fd = socket(AF_INET, SOCK_STREAM, 0);
		if  (fd < 0 ){
			perror ("socket");
			return -1;
		}

	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(port);
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&report,sizeof report);//Permite erutilizar el puerto sin esperar luego de cerrarlo
	if (bind(fd,(struct sockaddr *)&procrem, sizeof procrem) < 0 ) {
		perror ("bind");
                return -1;
        }

	listen(fd, 5);//5 usuarios max
	signal(SIGCHLD,SIG_IGN ); //para sacar procesos terminados de la PCB ...
	while ( (connfd = accept(fd,NULL, 0)) > 0 ){
		pid = fork();
		//hijo
		if ( pid == 0 ) {
				leido = read (connfd,buff ,sizeof buff);
				char * pch;
				int i=0;
  				pch = strtok (buff," ");
  				while (pch != NULL)
  				{	
				if(i==0){
          			        url = urlm(pch);
        				//printf("%s \n", url);
        				pagec = pagem(pch,url); 
        				//printf("%s \n", pagec);
					strcpy(con,url);
					strcat(con," HTTP/1.1\nHost: ");
					strcat(con,pagec);
					strcat(con,"\nConnection: close\n\n");
					strcpy(can,"GET ");
					strcat(can,con);
					//printf("%s \n",can);
				}
				if(i==1){
					strcpy(search,pch);
					//printf("search : %s \n",search);
				}
					//printf ("%s \n",pch);
    				
					pch = strtok (NULL, " ");
  					i++;
				}
				struct sockaddr_in serverhttp={};
        			fdcliente = socket(AF_INET, SOCK_STREAM, 0);
       				 if  (fdcliente < 0 ){
                			perror ("socketcliente");
                			return -1;
        			}
        			serverhttp.sin_family = AF_INET;
        			serverhttp.sin_port = htons(80);
        			struct hostent *hp = gethostbyname(pagec);
        			inet_pton(AF_INET,inet_ntoa( *(struct in_addr*)( hp -> h_addr_list[0])),&serverhttp.sin_addr);
        			conectado = connect(fdcliente,(struct sockaddr *)&serverhttp, sizeof serverhttp);
        			if  (conectado < 0 ){
                			perror ("connect");
                			return -1;
      				}
				
  				numpage = 0;
        			for(int x=0; can[x]; x++) {
        			numpage++;
        			}
        			numpage = numpage + 5;
				//printf("%d \n",numpage);

					char *ret ,*pos, *temp=NULL;
        				int z = 0,n=0,g=0,k=0 ,w = 0, p=0,j=0;
					write(fdcliente,can,numpage);
        			while((leido = read(fdcliente,buff,sizeof buff)) > 0){
					if  (leido < 0 ){
                				perror ("read");
                				return -1;
        				}
					for(int i = 0;  i < leido; i++) {
					ret = strstr(buff,search);
					temp=malloc(100*sizeof(char));
					if(ret){
					int resta=ret-buff;
					//printf("%d\n",su);
					while(*(buff+(resta+p))){
						if((*(buff+(resta+p))!='<') && (*(buff+(resta+(p+1)))!='/')){
							*(temp +j)=*(buff+(resta+p));
							j++;
						}
						else{
						printf("%s",temp);
						
						/*if(g==0){
						strcpy(letter,temp);
						}
						else{
						strcat(letter,temp);
						}
						*/
						
						g++;
						
						break;
						
						}
						p++;
						}
					}
					
					/*ret = strstr(buff,search);
                                        temp=malloc(100*sizeof(char));
                                        if(ret){
                                        int resta=ret-buff;
                                        //printf("%d\n",su);
                                        for(int i = resta;  i < (leido-1); i++,buff++) {

                                        //while(*(buff+(resta+p))){
                                                if((*(buff)!='<') && (*(buff+1))!='/'){
                                                        *(temp +j)=*(buff);
                                                        j++;
                                                }
                                                else{
                                                printf("%s",temp);
                                             
                                                g++;
                                                break;
                                                }
                                                p++;
                                                }
*/
					
//						printf("%s \n",letter);
					//if(isalnum(buff[i])){
					//if(isalnum(buff[i])){
					/*if(strcmp(buff,">") != 0){
*/

//						printf("%s \n",letter);
}		
        			
						//printf("%s \n",letter);
        		//write(connfd,letter,leido);
			}
			
						//write(1,letter,leido);
//        			write(connfd,temp,leido);
		return 0;
		}
	close(connfd);
	}
return 0;
}	
int portselect (int argc, char ** argv){
	getopt (argc, argv, "p::");	
	int port = atoi(argv[2]);
	return port;
      
		}
