#ifndef MOD_H_   
#define MOD_H_

void *user(void* connfd);  
char *dir(char* file);  
int conf(char* file);  
//char *pagem(char* string,char* url);
    extern char* file; 
	extern pthread_mutex_t mutex;
#endif // FOO_H_
