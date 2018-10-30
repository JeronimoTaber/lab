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
void *user(void *connfd) {
//	printf ("file %s \n",file);
	int id = 0;	
	id = (intptr_t)connfd;
	pthread_mutex_unlock(&mutex);
	int leido=0,sizedir=0,fd=0,leido2=0,size=0,leido3=0;
//	printf("id thread: %d \n",id);
	char buff[10000] = "",buff2[10000] = "",search[5] = "/",search2[5] = " ",dest[10000] ="",ptr[102400]="",dirstring[1000] = ""/*,dest2[1000] = ""*/;
        char *parsbeg=NULL, *parsend=NULL;
	char *dirsource = NULL;
	
	dirsource = dir(file);
	strcat(dirstring,dirsource);
	
        leido = read (id,buff ,sizeof buff);
        parsbeg = strstr(buff,search);
        parsend = strstr(parsbeg,search2);
        sizedir = parsend - parsbeg;
        sizedir--;
	strncpy(dest,&buff[5],sizedir);
	strcat(dirstring,dest);
	printf("file: %s \n",dirstring);	
	fd = open(dirstring , O_RDONLY);	
	if(fd == -1){//si no se puede abir el archivo muesta error
		char error404[1000] = "HTTP/1.0 404 Not Found \n";
		write (id,error404 ,24);
		perror("open");
		close(id);
		close(fd);
		pthread_exit(NULL);	
		return 0;
		//_exit(EXIT_FAILURE);

	}
	struct stat fileStat;
	fstat(fd,&fileStat);	
	//printf("File Size: \t\t%d bytes\n",fileStat.st_size);
        //printf("%d \n",sizedir);
	size = fileStat.st_size;
        char buffhttp[1000] = "HTTP/1.0 200 OK \n Content-lenght=";
	char bufflenght[1000];
	char str[10];
  //      sprintf(str,"%d",size);
	strcpy(bufflenght,str);
	char buffcontent[1000] = " \n Content-type=";
	

	char dot[5] = ".",bufftype[1000];
	char *last_tok = NULL,*tok = NULL;
	tok = strtok(dest, dot);
	while (tok){
		last_tok = tok;
		tok = strtok(NULL, dot);
	}
	if((strcmp(last_tok,"txt"))==0){
		char bufftypetxt[1000] = "text/plain \n\n";
		strcpy(bufftype,bufftypetxt);}
	if((strcmp(last_tok,"jpeg"))==0){
		char bufftypejpeg[1000] = "image/jpeg \n\n";
		strcpy(bufftype,bufftypejpeg);}
	if((strcmp(last_tok,"pdf"))==0){
		char bufftypepdf[1000] = "application/pdf \n\n";
		strcpy(bufftype,bufftypepdf);}
	if((strcmp(last_tok,"html"))==0){
		char bufftypehtml[1000] = "text/html \n\n";
		strcpy(bufftype,bufftypehtml);}
	int len = strlen(bufftype);
  
        int nDigits = floor(log10(abs(size))) + 1;
	write (id,buffhttp ,33);
	write (id,bufflenght , nDigits);
	write (id,buffcontent ,16);//16
	write (id,bufftype ,len);//16//jpeg21//text24
        read(fd, ptr, size);
        write (id,ptr,size);
        //o se puede usar
	//while((leido2  = read(fd, ptr, 102400)) > 0){
        //        write (id,ptr,leido2);
          //      }
	close(fd);
//	pthread_exit(NULL);

        close(id);
	pthread_exit(NULL);
//	return 0;

    }

