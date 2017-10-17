/**
 *  CS251 - Spring 2016: Project 1 Solution
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
    /* Use either optionA or optionB: */

    /* Option A: input/output using C like notation */
    FILE *inputfile = stdin;
	FILE *outputfile = stdout;

	/* Option B: input/output using C++ like notation would use "cin" and "cout" to read/write to stdin/stdout */

    /* ------------------------------------ */
    /* process input files and write output */
    /* ------------------------------------ */

    //Let the record show that I am not at all clever.

    char c;
    char form[4] = {' ',' ',' ','\0'};
    char num[4];
    num[3] = '\0';
    int cont = 0;
    int places = 0;
    int cols;
    char columns[20];


    while((c = fgetc(inputfile))!=EOF){
        if(c!='\n'&&cont<19){
            columns[cont++] = c;
        }
        else{
            break;
        }
    }
    columns[cont] = '\0';
    cols = atoi(columns);
    cont = 0;
    for(int i = 0; i<(6*cols-3); i++){
        printf("-");
    }
    printf("\n");
    if(cols!=0){
        while((c = fgetc(inputfile))!=EOF){
            while(c!=' '&&c!='\n'&&c!='\r'&&c!='\t'&&c!=EOF){
                num[places++] = c;

                c=fgetc(inputfile);

            }
            if(places>0){
                for(int i = 0; i<places; i++){
                    form[3-places+i] = num[i];
                }
                printf("%s",form);
                cont++;
                if(cont>=cols){
                    cont = 0;
                    printf("\n");
                }
                else{
                    printf(" | ");
                }
                places = 0;
                for(int i = 0; i<3; i++){
                    form[i] = ' ';
                }
            }
        }
    }
    for(int i = 0; i<(6*cols-3); i++){
        printf("-");
    }
    printf("\n");



    /* Close files if using C like notation */
    fclose(inputfile);
    fclose(outputfile);

    /* Exit the program */
    return 0;
}
