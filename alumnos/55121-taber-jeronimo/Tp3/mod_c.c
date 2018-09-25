#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void show(long count[]);
void mod_c(char *buffers ,sem_t *sem_c, sem_t *sem_cf, int *eof,int leido2) {
	int a = 0 ;
	long count [23] = {0};
 
	while(*eof ==  0){
		sem_wait(sem_cf);
		for(int i=0;i<leido2;i++){
		if(isalnum(buffers[i])){
                    	a++;
	                }
                else{	
                     	count[a]++;
                    	a=0;
                	}
                }
		sem_post(sem_c);
	}
	show(count);
	sem_wait(sem_cf);
	sem_post(sem_c);
}
void show(long count[]){
	for(int x=1;x<23;x++){
        	if(count[x] != 0){
                printf("Letras %d: ", x);
                printf(" %ld", count[x]);
                printf("\n");
        	}
	}
}
