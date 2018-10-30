#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mod.h"
char *urlm(char *string) {
    


   int day, year,numurl,numpage;
   char urlco[200], urlc[200], page[200], dtm[200],format[200];
   const char ch = '/';
   char *ret = NULL;
ret = (char *) malloc(sizeof (char));

   strcpy( dtm, string );
//	printf("string : %s \n",string);
//while ( *string ) printf( "%s\n", string++ );  
 sscanf( dtm, "http://%s", urlc);
//printf("url: %s \n",urlc);

        ret = strchr(urlc, ch);
     /*   numurl = 0;
        for(int m=0; urlc[m]; m++) {
        if(urlc[m] != ' ') {
        numurl ++;
         }
        }
printf("numurl : %d",numurl);
        numpage = 0;
        for(int x=0; ret[x]; x++) {
        if(ret[x] != ' ') {
        numpage ++;
         }
        }
        strcpy( urlco, urlc );
        int read = numurl - numpage;
        sprintf(format, "%%%ds", read);
        sscanf(urlco, format, page);
   printf("%s\n %s\n", page,ret);
*/	
   return ret;
}

