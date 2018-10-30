#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>//para gethostbyname
/*struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};
struct in_addr {
    unsigned long s_addr;  // load with inet_aton()
};*/
int main(int argc, char **argv){
	int fd, leido, conectado;
	char buff[1024];
	char buff2[1024];
	struct sockaddr_in procrem={};
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd < 0 ){
		perror ("socket");
		return -1;
	}
	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(80);
	//procrem.sin_addr = 192.168.1.52;
	//procrem.sin_addr.s_addr = htonl(0xc0a80134);
	/*struct hostent *hp = gethostbyname(argv[1]);
		if(hp == NULL){
		printf("gethostbyname");
		}
		else{
		printf("%s = ", hp -> h_name);
		unsigned int i=0;
		while(hp -> h_addr_list[i] != NULL){
			printf("%s ", inet_ntoa( *( struct in_addr*)(hp -> h_addr_list[i])));
			i++;
			}

		}
	*/
//	inet_pton(AF_INET,"192.168.1.247", &procrem.sin_addr);
	struct hostent *hp = gethostbyname("um.edu.ar");
	char ip[20];
	inet_pton(AF_INET,inet_ntoa( *(struct in_addr*)( hp -> h_addr_list[0])),&procrem.sin_addr);
	
	conectado = connect(fd,(struct sockaddr *)&procrem, sizeof procrem);
	if  (conectado < 0 ){
                perror ("connect");
                return -1;
      }

	
	write(fd, "GET /es/ua/fi.html HTTP/1.1\nHost: www.um.edu.ar\nConnection: close\n\n",67);
	while((leido = read(fd,buff,sizeof buff)) > 0){
	/*if  (leido < 0 ){
		perror ("read");
		return -1;
	}*/
	write(1,buff,leido);
	}
	return 0;
}	
