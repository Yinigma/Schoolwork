#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <regex.h>

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("Input a directory %d.\n", argc);
		exit(-1);
	}
	char * inDir = argv[1];
	int inLen = strlen(inDir);
    int wild = 0;
	int rDex = -1;
	int lDex = -1;
	char * finished = '\0';
	char * remaining = '\0';
	char * pattern = '\0';
	for(int i = 0; i < inLen; i++){
		if(i==0&&inDir[i]=='/'){
			continue;
		}
		if(inDir[i]=='*'||inDir[i]=='?'){
			wild = 1;
		}
		if(inDir[i]=='/'){
			if(wild==1&&(i!=(inDir-1))){
				rDex = i;
				break;
			}
			else{
				lDex = i;
			}
		}
	}
	if(wild==0){
		printf("No WildCards found.\n");
		printf("%s\n",inDir);
		exit(-1);
	}
	printf("lDex: %d\n",lDex);
	printf("rDex: %d\n",rDex);
	printf("%s\n",inDir);
	int rlen = 0;
	int flen = 0;
	int plen = 0;
	if(lDex!=-1){
		flen = lDex+1;
		finished = (char*) malloc(flen*sizeof(char));		
		memcpy(finished, inDir, flen-1);
		finished[flen] = '\0';
	}
	if(rDex!=-1){
		rlen = inLen-rDex;
		remaining = (char*) malloc(rlen*sizeof(char));		
		memcpy(remaining, (inDir+rDex+1), rlen-1);
		remaining[rlen] = '\0';
	}
	plen = inLen-rlen-flen+1;
	pattern = (char*) malloc(plen*sizeof(char));
	memcpy(pattern, (inDir+lDex+1), plen-1);
	pattern[plen] = '\0';
	
	printf("finished: %s\n",finished);
	printf("remaining: %s\n",remaining);
	printf("pattern: %s\n",pattern);
	
	char * conv = calloc(2*plen+1, sizeof(char));
	conv[0] = '^';
	//convert pattern
	int numAster = 0;
	for(int i = 0; i<(plen-1); i++){
		if(pattern[i]=='?'){
			conv[i+numAster+1]='.';
		}
		else if(pattern[i]=='*'){
			conv[i+numAster+1]='.';
			numAster++;
			conv[i+numAster+1]='*';
		}
		else{
			conv[i+numAster+1]=pattern[i];
		}
	}
	conv[plen+numAster+1] = '$';
	conv[plen+numAster+2] = '\0';
	realloc(conv, plen+numAster);

	printf("converted: %s\n",conv);

	//Everythings seperated. Let's go to hell.

	//set up regex
	regex_t re;
	int result = regcomp( &re, conv,  REG_EXTENDED|REG_NOSUB);
	if(result != 0) {
		fprintf( stderr, "Bad regex\n");
    }

	DIR* tameDir;
	struct dirent* dp;
	if(lDex!=-1){
		if((tameDir = opendir(finished)) == NULL){
			//return;
			printf("No such directory.\n");
			exit(2);
		}
	}
	else{
		tameDir = opendir(".");
	}

	int numMatches = 0;
	while ((dp = readdir(tameDir)) != NULL) {
		if(dp->d_type==DT_DIR){
			
			//Regex matching

			regmatch_t match;
			result = regexec( &re, dp->d_name, 1, &match, 0 );
			
			if(result==0){
				numMatches++;
			}
		}
	}
	closedir(tameDir);
	//Oh my god I'm actually doing this stupid shit.
	if(lDex!=-1){
		tameDir = opendir(finished);
	}
	else{
		tameDir = opendir(".");
	}
	char * matches[numMatches];
	int counter = 0;
	//Like holy fuck, I get the feeling this is not safe at all
	//I just can't think of a way to get a reliable buffer other than make it fucking huge or bring in an adt to this already ugly af function
	while ((dp = readdir(tameDir)) != NULL) {
		if(dp->d_type==DT_DIR){
			regmatch_t match;
			result = regexec( &re, dp->d_name, 1, &match, 0 );
			
			if(result==0){
				matches[counter] = dp->d_name;
				counter++;
			}
		}
	}
	closedir(tameDir);
	//sort
	int sorted = 0;
	while(!sorted){
		sorted = 1;
		for(int i = 0; i< numMatches-1; i++){
			if(strcmp(matches[i],matches[i+1])>0){
				char * temp = matches[i];
				matches[i] = matches[i+1];
				matches[i+1] = temp;
				sorted=0;
			}
		}
	}
	char * cOutDir;
	char * resDir;
	int outlen = 0;
	printf("Full directories to wildCardExpansion:\n");
	for(int i = 0; i< numMatches; i++){
		//When you have torn all your hair out from trying to get a list of alphabetized files, then you have my permission to recurse
		outlen = strlen(matches[i]);
		cOutDir = calloc(flen+rlen+outlen+1, sizeof(char));
		snprintf(cOutDir, flen+rlen+outlen+1, "%s/%s/%s\0", finished, matches[i], remaining);
		printf("%s\n", cOutDir);
	}
	
	return;//NULL;
}
