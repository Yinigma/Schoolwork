all: mytest

mytest: mytest.c problem_parse_words.c
	gcc -std=gnu99 -g -o mytest mytest.c problem_parse_words.c

clean:
	@ rm -f *.o *.out mytest 
