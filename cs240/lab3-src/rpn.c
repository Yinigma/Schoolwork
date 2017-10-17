
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
            stack_push(strtod(w,NULL));
        }
        else if(*w=='-'&&(*(w+1)-'0')>-1&&((*w+1)-'0')<10){
            stack_push(strtod(w,NULL));
        }
        else if(*w=='x'){
            stack_push(x);
        }
        else{
            if(stack_top()>0){
                if(strcmp(w,"sin")==0){
                stack_push(sin(stack_pop()));
                }
                else if(strcmp(w,"cos")==0){
                    stack_push(cos(stack_pop()));
                }
                else if(strcmp(w,"log")==0){
                    stack_push(log(stack_pop()));
                }
                else if(strcmp(w,"exp")==0){
                    stack_push(exp(stack_pop()));
                }
                else if(stack_top()>1){
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
                    if(strcmp(w,"pow")==0){
                        stack_push(pow(stack_pop(),stack_pop()));
                    }
                }
                else{
                    printf("Stack underflow\n");
                    exit(0);
                }
            }
            else{
                printf("Stack underflow\n");
                exit(0);
            }
        }
    }
    if(stack_top()>1){
        printf("Elements remain in the stack\n");
        exit(0);
    }
    return stack_pop();
}
