#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char * concatDir(char * dir){
    int maxLen = 512;
    char * out = (char *) calloc(maxLen, sizeof(char));
    getcwd(out, maxLen);
    int len = strlen(out);
    strncat(out,"http-root-dir",maxLen-len);
    len += 13;                                                      //length of "http-root-dir"
    bool initSlash = (dir[0]=='/');
    if(strstr("icons",dir)==NULL&&strstr("htdocs",dir)==NULL){
        strncat(out,"htdocs",maxLen-len);
        len+=7;                                                     //number of "/htdocs"
    }
    strncat(out,dir,maxLen-len);
    return out;
}
char * truncDir(char * dir){
    int len = strlen(dir);
    int copyDex = 0;
    char * out = (char *) calloc(len, sizeof(char));
    for(int i = 0; i<len; i++){
        if(i<len-2&&dir[i+1]=='.'&&dir[i+2]&&dir[i]=='/'){
            if(i==0){
                return NULL;
            }
            int dif = 1;
            while(i-dif>=0&&dir[i-dif]!='/'){
                copyDex--;
                dif++;
                if(copyDex<0){
                    return NULL;
                }
            }
            i+=3;
            if(i+1<len){
                i++;
            }
        }
        out[copyDex] = dir[i];
        copyDex++;
    }
    out[copyDex] = '\0';
    return out;
}

int main(){
    char * cwd = truncDir("/dingo/blibble/../griblittle/asciimatt/ogg/asdf/..");
    printf("%s\n",cwd);

}
