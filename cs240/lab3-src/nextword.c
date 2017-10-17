
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL.
char * nextword(FILE * fd) {
  	int c;
	int i = 0;
	while((c=fgetc(fd))!=EOF){
	  if(c=='\0'||c==' '||c=='\n'||c=='\t'||c=='\r'){
            if(i>0){
                word[i]='\0';
                return word;
            }
            else{
                continue;
            }

	  }
	  else{
            word[i]=c;
            i++;
	  }
    }
	if(i>0){
		word[i]='\0';
		return word;
	}
	fclose(fd);
	return NULL;
}
