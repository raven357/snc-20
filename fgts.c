#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define LINE_SIZE 1024

int main()
{
    char buf[LINE_SIZE];
    FILE *f;
    int count= 0;
    if ((f = fopen("fgts.c", "r")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}
      
  while(fgets(buf, LINE_SIZE, f)!= NULL){
    if(strlen(buf)== 1){
           ++count;
           if(count>= 2){
            printf("%ld ok\n", strlen(buf)); 
            
            }
        }
        else {
           count= 0;
        }          
                      
    }
}



