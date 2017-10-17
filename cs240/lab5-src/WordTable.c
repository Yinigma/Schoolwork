
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "WordTable.h"


void toLower(char *s);

// Initializes a word table
void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++) {
		llist_init(&wtable->wordArray[i].positions);
	}
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	// Find first word if it exists
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			// Found word. Add position in the list of positions
			llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
	}

	if(wtable->nWords+1>=wtable->maxWords){
        wtable->maxWords+=1;
        wtable->wordArray = (WordInfo *) realloc(wtable->wordArray, wtable->maxWords * sizeof(WordInfo));
        if(wtable->wordArray==NULL){
            printf("Not enough memory!\n");
            exit(1);
        }
	}
	wtable->wordArray[wtable->nWords].word = strdup(word);
	wtable->wordArray[wtable->nWords].positions.head = NULL;
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++) {
		fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
		llist_print(&wtable->wordArray[i].positions);
	}
}

// Get positions where the word occurs
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{
	for (int i = 0; i < wtable->nWords; i++) {
		if (strcmp(wtable->wordArray[i].word, word)== 0 ) {
                    return &wtable->wordArray[i].positions;
		}
	}
	return NULL;
}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos;

// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
	// Write your code here
	char * str;
	char c = 0;
	while((c = fgetc(fd))!=EOF){
        charCount++;
        while((c>='A'&&c<='Z')||(c>='a'&&c<='z')){//c!=EOF&&c!=' '&&c!='\r'&&c!='\t'&&c!='\n'
            word[wordLength++]=c;
            c = fgetc(fd);
            charCount++;
        }
        if(wordLength>0){
            word[wordLength] = '\0';
            str  = (char *) malloc((wordLength+1)*sizeof(char));
            str = strcpy(str,word);
            wordLength = 0;
            toLower(str);
            return str;
        }
	}
	return NULL;
}

// Convert string to lower case
void toLower(char *s) {
	while(*s){
        if(*s>='A'&&*s<='Z'){
            *s = *s - 'A' + 'a';
        }
        s++;
	}
}


// Read a file and obtain words and positions of the words and save them in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int verbose) {
	FILE * fp = fopen(fileName, "r");
	if(fp==NULL){
            return 0;
	}
	int iter = 0;
	char * str;
	while((str = nextword(fp))!=NULL){
	    if(verbose){
		int pos = charCount-strlen(str)-1;
		printf("%d: word=%s, pos=%d\n",iter++,str,pos);
	    }
            wtable_add(wtable,str,charCount-strlen(str)-1);
	}
	//wtable_print(wtable,stdout);
	return 0;
}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
    int sorted = 0;
    while(!sorted){
        sorted = 1;
        for(int i = 0; i<wtable->nWords-1; i++){
            if(strcmp(wtable->wordArray[i].word,wtable->wordArray[i+1].word)>0){
                sorted = 0;
                WordInfo temp = wtable->wordArray[i];
                wtable->wordArray[i] = wtable->wordArray[i+1];
                wtable->wordArray[i+1]=temp;
            }
        }
    }
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info.
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
    FILE * fp = fopen(fileName, "r");
	if(fp==NULL){
        return 0;
	}
	printf("===== Segments for word \"%s\" in book \"%s\" =====\n",word,fileName);
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
            ListNode * c = wtable->wordArray[i].positions.head;
            while(c!=NULL){
                fseek(fp, c->value * sizeof(char),SEEK_SET);
                printf("---------- pos=%d-----\n",c->value);
                printf("......");
                for(int j = 0; j<200; j++){
                    printf("%c",fgetc(fp));
                }
                printf("......\n");
                c = c->next;
            }
		}
	}
	return 0;
}
