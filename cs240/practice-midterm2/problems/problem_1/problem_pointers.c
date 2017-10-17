#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Problem (1/4)
/******************************************************************************
 * TODO: Print the array.
 *       The format should be (array index)(colon)(array element)(newline)
 *
 * Parameters: n -- the number of elements in the array
 *             array -- a double array
 *
 * Return: void
 *
 * Return Type: void
 *****************************************************************************/
void printArray(int n, double * array) {
    int cont = 0;
    while(n - cont){
        printf("%d:%f\n",cont,*array);
        array++;
        cont++;
    }
}

// Problem (2/4)
/******************************************************************************
 * TODO: Return the minimum element of array
 *
 * Parameters: array -- a double array
 *             n -- the number of elements in the array
 *
 * Return: minimum element in array
 *
 * Return Type: double
 *****************************************************************************/
double minArray(int n, double * array) {
    double min = *array++;
    int cont = 1;
    while(n-cont){
        if(*array<min){
            min = *array;
        }

    }
	return 0;
}

// Problem ( 3/4 )
/******************************************************************************
 * TODO: Reverse the given string 'str'.
 * E.g. reverse_str("smile") should return "elims"
 *
 * Parameters: str -- The given string to be reversed.
 *
 * Return: A pointer to str, str should be reversed
 *
 * Return Type: char pointer
 *****************************************************************************/
char * reverse_str (char * str ) {
    int len = strlen(str);
    char temp;
    for(int i = 0; i<(len/2); i++){
        temp = *(str+i);
        *(str+i) = *(str+len-i-1);
        *(str+len-i-1) = temp;
    }
    return str;
}

// Problem ( 4/4 )
/******************************************************************************
 * TODO: Determine if the string str2 is a permutation of str1. A permutation
 * is the rearranging of characters in a different order.
 * E.g. the string "act" is a permutation of "cat"
 *
 * Hint: count the occurences of each letter
 *
 * Parameters: str1 -- The original string
 *	       str2 -- Determine if this string is a permutation of str1
 *
 * Return: 1 if str2 is a permutation
 *         0 if str2 is not a permutation
 *
 * Return Type: integer
 *****************************************************************************/
int is_permutation ( char * str1, char * str2 ) {
    int len = strlen(str1);
    int counter = 0;
    if(len-strlen(str2)!=0){
        return 0;
    }
    for(int i = 0; i<len; i++){
        for(int j = 0; j<len; j++){
            if(*(str1+i)==*(str1+j)){
                counter++;
            }
            if(*(str1+i)==*(str2+j)){
                counter--;
            }
        }
        if(counter!=0){
            return 0;
        }
    }
    return 1;
}

