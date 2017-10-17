#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Problem ( 1/3 )
/******************************************************************************
 * TODO: Count the number of lines in the file named 'fileName'. Return the
 * number of lines as an integer.
 *
 * Parameters: fileName -- name of the file
 *
 * Return: number of lines in the file
 *
 * Return Type: integer
 *****************************************************************************/
int countLines(char * fileName) {
    // Write Your Code Here
	int i = 0;
	char c;
	FILE* fd = fopen(fileName, "r");
	while((c = fgetc(fd))!=EOF){
		if(c == '\n'){
			i++;
		}
	}
    return i;
}

// Problem ( 2/3 )
/******************************************************************************
 * TODO: Read the text file, parse each word, and store the word in to the
 * 'word_list'. Change all the characters in the word to capital letters.
 * Return 'word_list'.
 *
 * E.g. a text file contains "Hello, world"
 *      The string array 'word_list' should contain {"HELLO", "WORLD"}
 *
 * Parameters: fileName -- name of the file
 *             word_list -- seperate the words from the text file and store
 *             each word in to this string array. Make sure to change all the
 *             characters in the word to upper case.
 *
 * Return: return the string array 'word_list'
 *
 * Return Type: char double pointer (String array)
 *****************************************************************************/

char ** create_word_list( char * fileName, char ** word_list ) {
    char* word;
    word = (char*) malloc(200 * sizeof(char));
	int len = 0;
	char c;
	int numWords = 0;
    FILE* fd = fopen(fileName, "r");
	while((c = fgetc(fd))!=EOF){
		if(c=='\0'||c==' '||c=='\n'||c=='\t'||c=='\r'||c=='-'){
            //On a whitespace character
            if(len>0){
				//put the word in the list if there is one
				word[len] = '\0';
				word_list[numWords] = strdup(word);
				numWords++;
				len = 0;
			}

            else{
                //otherwise keep going (until it isn't a space)
                continue;
            }
		}
		else{
            //On a non-whitespace character, add the character to the current word
            if(c>='a'&&c<='z'){
                c = c-'a'+'A';
            }
            if(c>='A'&&c<='Z'){
                word[len++] = c;
            }
		}
	}
	if(len>0){
        //add anything that's left
        word[len] = '\0';
        word_list[numWords] = strdup(word);
        numWords++;
        len = 0;
	}
	free(word);
    return word_list;
}

// Problem ( 3/3 )
/******************************************************************************
 * TODO: Iterate through the list of words in each file. If a word is found in
 * both files, add the word to 'match_list'. Do not repeat words in the list.
 * Capitilization of words does not matter. So "Bob" and "bob" should be
 * considered a match. When inserting the word in to the list, make all the
 * characters in the word upper case.
 *
 *  HINT: Use the function create_word_list to save time.
 *
 * E.g. File1 contains the text "We like fruit. It is good."
 *      File2 contains the text "Fruit is very delicious."
 *
 *      The string array 'match_list' should contain {"FRUIT", "IS"}
 *
 * Parameters: fileName1 -- name of the first text file
 *	       fileName2 -- name of the second text file
 *	       match_list -- store the intersecting words from both files in
 *	                     this string array.
 *
 * Return: Return the string array 'match_list'.
 *
 * Return Type: char double pointer (String array)
 *****************************************************************************/
char ** sharedWords( char * fileName1, char * fileName2, char ** match_list ) {
    char** l1;
    l1 = (char **) malloc (200 * sizeof(char *));
    for(int i = 0; i<200; i++){
        l1[i] = strdup("");
    }
    create_word_list(fileName1, l1);
    char** l2;
    l2 = (char **) malloc (200 * sizeof(char *));
    for(int i = 0; i<200; i++){
        l2[i] = strdup("");
    }
    create_word_list(fileName2, l2);
    int unmatched = 1;
    int numWords = 0;
    for(int i = 0; strcmp(l1[i],"")!=0; i++){
        for(int j = 0; strcmp(l2[j],"")!=0; j++){
            if(strcmp(l1[i],l2[j])==0){
                for(int k = 0; strcmp(match_list[k],"")!=0; k++){
                    if(strcmp(l1[i],match_list[k])==0){
                        unmatched = 0;
                    }
                }
                if(unmatched){
                    match_list[numWords++] = strdup(l1[i]);
                }
                unmatched = 1;
            }
        }
    }
    return match_list;
}
