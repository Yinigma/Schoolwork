#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//

//
// See test_sort to see how to use mysort.
/**
 * @brief Arbitrary sort func
 *
 * Sort an array of element of any type
 * using "compFunc" to sort the elements.
 * 
 * The elements are sorted such as:
 * 
 * if ascending != 0
 *   compFunc( array[ i ], array[ i+1 ] ) <= 0
 * else
 *   compFunc( array[ i ], array[ i+1 ] ) >= 0
 * 
 * @param n Number of elements.
 * @param elementSize Size of each element.
 * @param array Pointer to an array of arbitrary type.
 * @param ascending Boolean controlling the direction of the sort.
 * @param compFunc Comparison funciton.
 **/



void mysort(int n, int elementSize, void * array, int ascending, CompareFunction compFunc)
{
	int nSorted = 1;
	if(ascending){
		while(nSorted){
			nSorted = 0;
			for(int i=0; i<n-1; i++){
				int com = (compFunc(array+(i*elementSize),array+((i+1)*elementSize)));
				if(com>0){
					char * temp = (char*) malloc(elementSize);
					memcpy(temp,array+(i*elementSize),elementSize);
					memcpy(array+(i*elementSize),array+((i+1)*elementSize),elementSize);
					memcpy(array+((i+1)*elementSize),temp,elementSize);
					nSorted = 1;
				}
			}
		}
	}
	else{
		while(nSorted){
			nSorted = 0;
			for(int i=0; i<n-1; i++){
				int com = (compFunc(array+(i*elementSize),array+((i+1)*elementSize)));
				if(com<0){
					char * temp = (char*) malloc(elementSize);
					memcpy(temp,array+(i*elementSize),elementSize);
					memcpy(array+(i*elementSize),array+((i+1)*elementSize),elementSize);
					memcpy(array+((i+1)*elementSize),temp,elementSize);
					nSorted = 1;
				}
			}
		}
	}
}

