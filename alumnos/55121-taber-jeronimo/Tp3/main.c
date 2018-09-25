#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

int fileopen(int argc, char ** argv);
extern void mod_c();
extern void mod_u();
int main(int argc, char ** argv){
	int *leido2 = NULL;	
	int leido,pidc,pidu;
	char *ptr=NULL, *sema=NULL;
	sem_t *sem_c,*sem_cf,*sem_u,*sem_uf,*sem_en;
	int fd = fileopen(argc, argv);//llama a funcion fileopen
	ptr = mmap(NULL,sizeof(ptr),PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
        int *eof = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

	leido2 = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	sema = mmap(NULL,5*sizeof(sem_t),PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	*eof=0;
	sem_u = (sem_t *)sema;
	sem_c = sem_u + sizeof(sem_u);
	sem_uf = sem_c + sizeof(sem_c);
	sem_cf = sem_uf + sizeof(sem_uf);
	sem_en = sem_cf + sizeof(sem_cf);
	sem_init(sem_c,1,0);
	sem_init(sem_cf,1,0);
	sem_init(sem_u,1,0);
	sem_init(sem_uf,1,0);
	sem_init(sem_en,1,0);


     
	//hijo counter
	if((pidc = fork()) == 0){
	printf("hola soy el hijo que cuenta \n");	
	mod_c(ptr, sem_c,sem_cf,eof,*leido2);	
	return 0;	
	}
	//hijo upper
        if((pidu = fork()) == 0){
	printf("hola soy el segundo hijo que pasa a mayuscula \n");	
	mod_u(ptr,sem_u,sem_uf,eof,*leido2);	
	return 0;
        }

	while((*leido2  = read(fd, ptr, sizeof ptr)) > 0) {
		sem_post(sem_cf);
		sem_post(sem_uf);	
		sem_wait(sem_c);
		sem_wait(sem_u);
	
		}
	*eof=1;
	sem_post(sem_cf);
	sem_wait(sem_c);
	return 0;
}
int fileopen (int argc, char ** argv){//abre el archivo ingrasado
	getopt(argc, argv, "f:");//agarra el nombre del archivo
	int fd = open(optarg, O_RDONLY);//abre archivo
	if(fd == -1){//si no se puede abir el archivo muesta error
		perror("open");
		_exit(EXIT_FAILURE);

	}
	return fd;//devuelve archivo
}
