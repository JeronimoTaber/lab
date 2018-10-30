#include <stdio.h>
#include <semaphore.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mod.h"
void upper(char *str);
void mod_u(char *buffer, sem_t *sem_u, sem_t *sem_uf,int *eof,int leido2) {

	char str[22] = "";
        int k = 0;
        int n;
        while(*eof == 0) {
                sem_wait(sem_uf);
                for(int i = 0;  i < leido2; i++) {
                        if(isalnum(buffer[i])) {
                                        str[k++] = buffer[i];
                        }
                        else {
                                str[k] = '\0';
                                upper(str);
                              	printf("%s%c",str,buffer[i]);
                                k = 0;
                        }
                }
                sem_post(sem_u);
        }
}



void upper(char *str) {
        if(strcmp(str, "Retrieved")  == 0 || strcmp(str, "cooperation") == 0 || strcmp(str, "wench") == 0 || strcmp(str, "buggy") == 0 || strcmp(str,     "len") == 0 || strcmp(str, "print") == 0)
                for(int i = 0; i < strlen(str); i++)
                        str[i] = toupper(str[i]);
}

