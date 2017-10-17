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
    double * tmp = array;
    for (int i = 0; i < n; i++) {
	printf("%d:%f\n", i, *tmp++);	
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
    if (n <= 0 ) {
	return 0;
    }
    int min = *array;
    double * tmp = array;
    for (int i = 0; i < n; ++i) {
	if ( *tmp < min ) {	
	    min = *tmp;
	}
	tmp++;
    }
    return min;
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
    // Write Your Code Here
    char * end = str;
    while ( *end ) {
	end++;
    }
    end--;
    char tmp;
    char * p = str;
    int len = strlen(str);    
    for (int i = 0; i < len/2; i++) {
	tmp = *p;
	*p = *end;
	*end = tmp;
	p++;
	end--;
    }
    return str;
 }

// Problem ( 4/4 ) 
/******************************************************************************
 * TODO: Determine if the string str2 is a permutation of str1. A permutation
 * is the rearranging of characters in a different order. 
 * E.g. the string "act" is a permutation of "cat" 
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
    // Write Your Code Here    
    int a1 [26];
    int a2 [26];
    
    for (int i = 0; i < 26; i++) {
	a1[i] = 0;
	a2[i] = 0;
    }

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    for (int i = 0; i < len1; i++) {
	int index = (int) (str1[i] - 'a');		
	a1[index]++;
    }
    for (int i = 0; i < len2; i++) {
	int index = (int) (str2[i] - 'a');		
	a2[index]++;
    }
    for (int i = 0; i < 26; i++) {
	if (a1[i] != a2[i]) {
	    return 0;
	}
    }
    return 1;
}
