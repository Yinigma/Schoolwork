#include <stdio.h>
#include <string.h>

int my_str_len(char * str);
char * my_str_cat(char * dest, char * src); 
char * my_str_cpy(char * dest, char * src);

void test1() {
	int l = my_str_len("Hello world");
	printf("my_str_len(\"Hello world\")=%d\n", l);

	l = my_str_len("CS240 Programming in C");
	printf("my_str_len(\"CS240 Programming in C\")=%d\n", l);

	l = my_str_len("");
	printf("my_str_len(\"\")=%d\n", l);
}

void test2() {
    char a[200];
    char * b;
    strcpy(a, "Hello world");
    b = my_str_cat(a, ", CS240 C Programming");
    b = my_str_cat(a, ", This is a great course");
    printf("\"%s\"\n", a);
    printf("\"%s\"\n", b);

    strcpy(a, "");
    b = my_str_cat(a, "");
    b = my_str_cat(b, "Hello");

    printf("\"%s\"\n", a);
    printf("\"%s\"\n", b);
}

void test3() {
    char a [200];
    char * b;
    b = my_str_cpy(a, "Hello world");
    printf("\"%s\"\n", a);
    printf("\"%s\"\n", b);

    b = my_str_cpy(a, "");
    printf("\"%s\"\n", a);
    printf("\"%s\"\n", b);
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
	else {
	    printf("This is not a test case\n");
	}
}
