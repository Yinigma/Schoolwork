#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function Declaration
int countLines(char * fileName);
char ** create_word_list(char * fileName, char ** list); 
char ** sharedWords(char * fileName1, char * fileName2, char ** list);

// Test Functions
void test1() {
    char * fileName = "files/alice.txt";
    int numLines = countLines(fileName);
    printf("Number of lines in File 1 = %d\n", numLines);


    fileName = "files/two_cities.txt";
    numLines = countLines(fileName);
    printf("Number of lines in File 2 = %d\n", numLines);
}

void test2() {
    char ** list;
    list = (char **) malloc (200 * sizeof(char *));
    for (int i = 0; i < 200; i++) {
	list[i] = strdup("");
    }

    create_word_list("files/simple.txt", list);
    for (int i = 0; strcmp(list[i], "") != 0; i++) {
	printf("Word[%d]: %s\n", i, list[i]);
    }
}

void test3() {
    char ** list;
    list = (char **) malloc (200 * sizeof(char *));
    for (int i = 0; i < 200; i++) {
	list[i] = strdup("");
    }

    create_word_list("files/two_cities.txt", list);
    for (int i = 0; strcmp(list[i], "") != 0; i++) {
	printf("Word[%d]: %s\n", i, list[i]);
    }
}

void test4() {
    char ** list;
    list = (char **) malloc (200 * sizeof(char *));
    for (int i = 0; i < 200; i++) {
	list[i] = strdup("");
    }
    list = sharedWords("files/alice.txt", "files/two_cities.txt", list);

    // Sorts the list so the user and test case have same output
    for (int i = 0; strcmp(list[i], "") != 0; i++) {
	for (int j = 0; strcmp(list[j+1], "") != 0; j++) {
	    if ( strcmp(list[j], list[j+1]) > 0 ) {
		char * tmp = strdup(list[j]);
		list[j] = list[j+1];
		list[j+1] = tmp;
	    }
	}
    }

    for (int i = 0; strcmp(list[i], "") != 0; i++) {
	printf("Word[%d]: %s\n", i, list[i]);
    }
}

int main(int argc, char ** argv) {
    if (argc != 2) {
	printf("Usage Error: mytest test1 .. test2 .. test3\n");
	return -1;
    }
    if (!strcmp(argv[1], "test1")) {
	test1();
    }
    else if (!strcmp(argv[1], "test2")) {
	test2();
    }
    else if (!strcmp(argv[1], "test3")) {
	test3();
    }
    else if (!strcmp(argv[1], "test4")) {
	test4();
    }
    else {
	printf("That is not a test case\n");
    }
}
