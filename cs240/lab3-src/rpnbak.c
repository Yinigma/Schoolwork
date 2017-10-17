
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {

    char* w;
    double s=0;
    int i = 0;
    double res = 0;

    FILE * fd = fopen(fileName, "r");
    if (fd == NULL) {
        printf("Could not open file %s\n", fileName);
        exit(1);
    }
    while ((w = nextword(fd)) != NULL) {
        if((*w-'0')>-1&&(*w-'0')<10){
	    //printf("Entered positive num if statement.\n");
            stack_push(strtod(w,NULL));
        }
        else if(*w=='-'&&(*(w+1)-'0')>-1&&((*w+1)-'0')<10){
	    //printf("Entered negative num if statement.\n");
            stack_push(strtod(w,NULL));
        }
        else if(*w=='x'){
            stack_push(x);
        }
        else{
            switch(*w){
                case '+':
                    stack_push(stack_pop()+stack_pop());
                    break;
                case '-':
                    s = stack_pop();
                    stack_push(stack_pop()-s);
                    break;
                case '*':
                    stack_push(stack_pop()*stack_pop());
                    break;
                case '/':
                    s = stack_pop();
                    stack_push(stack_pop()/s);
                    break;
            }
            if(strcmp(w,"sin")==0){
		printf("enetered sin if statement.\n");
                stack_push(sin(stack_pop()));
            }
            if(strcmp(w,"cos")==0){
		printf("enetered cos if statement.\n");
                stack_push(cos(stack_pop()));
            }
            if(strcmp(w,"pow")==0){
		printf("enetered pow if statement.\n");
                s = stack_pop();
                stack_push(pow(s,stack_pop()));
            }
            if(strcmp(w,"log")==0){
		printf("enetered log if statement.\n");
                stack_push(log(stack_pop()));
            }
            if(strcmp(w,"exp")==0){
		printf("enetered exp if statement.\n");
                stack_push(exp(stack_pop()));
            }
        }
    }
    stack_print();
    return stack_pop();
}
