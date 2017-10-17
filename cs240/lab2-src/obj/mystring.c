
#include <stdlib.h>
#include "mystring.h"
#include <stdio.h>

// Type "man string" to see what every function expects.
// ^ What?


int mystrlen(char * s) {
    int i = 0;
	while(*s){
        *s++;
        i++;
	}
	return i;
}

char * mystrcpy(char * dest, char * src) {
    char *s = dest;
    while(*src!=0){
        *dest = *src;
        dest++;
        src++;
    }
    *dest = 0;
    return s;
    /*int i =0;
    while(src[i]!='\0'){
        dest[i]=src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;*/
}

char * mystrcat(char * dest, char * src) {
    char *s = dest;
    dest+=mystrlen(dest);
    while(*src){
        *dest = *src;
        dest++;
        src++;
    }
    *dest = 0;
    return s;
}

int mystrcmp(char * s1, char * s2) {
    int len1=mystrlen(s1);
    int len2=mystrlen(s2);
    while(*s1!=0){
        if(*s1>*s2){
            return 1;
        }
        else if(*s1>*s2){
            return -1;
        }
        s1++;
        s2++;
    }
    if(len1==len2){
        return 0;
    }
    else if(len1>len2){
        return 1;
    }
    return -1;
}

char * mystrstr(char * hay, char * needle) {
    char *start = needle;
    char *found = NULL;
    int ineff = 1;
    while(*hay){
        if(*hay==*needle){
            found = hay;
            while(*needle){
                if(*hay!=*needle){
                    needle=start;
                    ineff = 0;
                    break;
                }
                hay++; needle++;
            }
            if(ineff){
                return found;
            }
            ineff = 1;
        }
        hay++;
    }
	return NULL;
}

char * mystrdup(char * s) {
	char *dup = malloc(mystrlen(s)+1);
	mystrcpy(dup,s);
	return dup;
}

char * mymemcpy(char * dest, char * src, int n){
    char *s = dest;
	while(n>0){
        *dest=*src;
        dest++;
        src++;
        n--;
	}
	return s;
}

