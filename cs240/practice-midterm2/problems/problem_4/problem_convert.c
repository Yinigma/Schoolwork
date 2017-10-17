#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_DIGITS 32

// Problem (1/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting an integer
 *             base   -- the base of the number you are given
 *
 * Return: The number as an integer
 *
 * Return Type: int
*****************************************************************************/
int toInteger(char * number, int base) {
    int len = strlen(number);
    int num =1;
    int dec = 0;
    while(*number){
        if(*number>='0'&&*number<='9'){
            num = *number - '0';
        }
        else if(*number>='A'&&*number<='O'){
            num = *number - 'A'+10;
        }
        else if(*number>='a'&&*number<='o'){
            num = *number - 'a';
        }
        int i;
        int power = 1;
        for(i = 0; i<(len-1);i++){
            power*=base;
        }
        dec+=(num*power);
        len--;
        number++;

    }
	return dec;
}

// Problem (2/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting a string
 *             base   -- the base you are converting the numebr to
 *
 * Return: The number as a string in base "base"
 *
 * Return Type: char *
*****************************************************************************/
char * toBase(int number, int base) {
	char * conv;
	int tnum = number;
	int len = 0;
	int c;
	while(tnum){
        tnum/=base;
        len++;
	}
	conv = (char *) malloc((len)*sizeof(char));
	conv[len] = '\0';
	len--;
	tnum = number;
	while(tnum){
        c = tnum%base;
        //find char, put in string
        if(c<10){
            *(conv+len) = '0'+ c;
        }
        else if(c>9&&c<26){
            *(conv+len) = 'A'+c-10;
        }
        len--;
        tnum/=base;
	}
	return conv;
}

