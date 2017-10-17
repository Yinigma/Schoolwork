#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Function Declaration
void printRange(int low, int high);
void printString(char * str);

// Test Function
void test1() {
	printf("Printing Range from 5 to 23\n");
	printRange(5, 23);
	printf("Printing Range from 3 to 15\n");
	printRange(3, 15);
}


void test2() {
	printf("Printing Hello World\n");
	printString("Hello World");
	printf("Printing Coca-Cola\n");
	printString("Coca-Cola");
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
	else {
	    printf("That is not a test case\n");
	}

}

