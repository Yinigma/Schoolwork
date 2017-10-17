#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"

// Problem ( 1/4 ) 
/******************************************************************************
 * TODO: Return the number of elements (ListNodes) in the linked list.
 *
 * Parameters: list -- find the number of elements contained in this single
 * linked list
 *
 * Return: the number of elements 
 *
 * Return Type: integer
 *****************************************************************************/
int llist_number_elements(LinkedList * list) {
    // Write Your Code Here
    ListNode * e = list->head;
    int len = 0;
    while (e != NULL) {
	len++;
	e = e->next;
    }
    return len;
}

// Problem ( 2/4 ) 
/******************************************************************************
 * TODO: Create a new ListNode and add it to the end of the single linked
 * 	 list. There is no check if the value exists in the list. 
 *
 * Parameters: list -- The single linked list to which you will insert the new
 * 		       ListNode to the end of.
 *             value -- The new ListNode will contain this value.
 *
 * Return: void
 * 
 * Return Type: void
 *****************************************************************************/
void llist_insert_last(LinkedList * list, int value) {
    // Write Your Code Here
    if (list->head == NULL) {
	list->head = (ListNode *) malloc(sizeof(ListNode));
	list->head->value = value;
	list->head->next = NULL;
    }
    else {
	ListNode * e = list->head;
	while (e->next != NULL) {
	    e = e->next;
	}
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	n->next = NULL;
	e->next = n;
    }
}

// Problem ( 3/4 )
/******************************************************************************
 * TODO: Remove the ith entry from the single linked list.   	 
 * 
 * Parameters: list -- The single linked list to which you will be removing
 * 		       the listNode from.
 * 	       ith -- The index where you will remove the listNode from the
 * 	              single linked list. 
 *
 * Return: Return 1 if the ListNode is removed.
 * 	   Return 0 if the ith entry does not exist in the list or the list is
 * 	   empty.
 *
 * Return Type: integer
 *****************************************************************************/
int llist_remove_ith(LinkedList * list, int ith) {
    // Write Your Code Here
    ListNode * e = list->head;
    int i = 0;
    ListNode * prev = NULL;
    while (1) {
	if (e == NULL) {
	    return 0;
	}
	if (i == ith) {
	    prev->next = e->next;
	    free(e);
	    return 1;
	}
	prev = e;
	e = e->next;
	i++;
    }
}

// Problem ( 4/4 )
/******************************************************************************
 * TODO: Iterate through list1 and list2. Check if any values intersect between
 *       the two lists. If the values match, add the intersecting elements
 *       to list3. Use the function llist_add(LinkedList * list, int value)
 *       to add a value to the list.
 * 
 * Parameters: list1 -- singled linked list, find values that intersect with
 *                      list2
 *             list2 -- single linked list, find values that intersect with
 *                      list1
 *             list3 -- store the intersection of list1 and list2 in this list
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void llist_intersection(LinkedList * list1, LinkedList * list2,
	LinkedList * list3) {
    // Write Your Code Here
    ListNode * e = list1->head;
    ListNode * f = list2->head;
    while ( e != NULL) {
	f = list2->head;
	while (f != NULL) {
	    if (e->value == f->value){
		llist_add(list3, e->value);
	    }
	    f = f->next;
	}
	e = e->next;
    }
}
