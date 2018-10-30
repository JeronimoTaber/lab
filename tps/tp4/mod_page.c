#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod.h"
char *pagem(char *string,char *url) {
    
   int day, year,numurl,numpage;
   char urlco[2000], urlc[2000], page[2000], dtm[2000],format[2000];
   const char ch = '/';
   char *ret = NULL;
	ret = (char *) malloc(sizeof (char));
//printf("string : %s \n",string);
//printf("url : %s \n",url);
   	strcpy( dtm, string );
 	sscanf( dtm, "http://%s", urlc);
        numurl = 0;
        for(int m=0; urlc[m]; m++) {
        if(urlc[m] != ' ') {
        numurl ++;
         }
        }
        numpage = 0;
        for(int x=0; url[x]; x++) {
        if(ret[x] != ' ') {
        numpage ++;
         }
        }
        strcpy( urlco, urlc );
	
        int read = numurl - numpage;
        sprintf(format, "%%%ds", read);
        sscanf(urlco, format, page);
//	printf("page : %s \n",page);
	ret = page;	
   return ret;
}

