
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {

	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;

	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
	ListNode * c = list->head;
	while(c!=NULL){
		if(c->value==value){
			return 1;
		}
		c = c->next;
	}
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode * c = list->head;
	while(c->next!=NULL){
		if(c->next->value==value){
			ListNode * temp = c->next;
			c->next = c->next->next;
			free(temp);
			return 1;
		}
		c = c->next;
	}
	return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	ListNode * c = list->head;
	while(ith){
		if(c==NULL){
			return 0;
		}
		c = c->next;
		ith--;
	}
	*value = c->value;
	return 1;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
    ListNode * c = list->head;
	while(--ith){
		if(c->next==NULL){
			return 0;
		}
		c = c->next;
	}
	ListNode * temp = c->next;
	c->next = c->next->next;
	free(temp);
	return 1;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	int i = 0;
	ListNode * c = list->head;
	while(c!=NULL){
		c = c->next;
		i++;
	}
	return i;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
    if(strchr(file_name, '/')!=NULL){
        return 0;
    }
    FILE *fp = fopen(file_name,"w+");
	ListNode * c = list->head;
	while (c != NULL) {
		fprintf(fp,"%d\n",c->value);
		c = c->next;
	}
	fclose(fp);
	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries,
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
    if(strchr(file_name, '/')!=NULL){
        return 0;
    }

    FILE *fp = fopen(file_name,"r");
    if(fp==NULL){
        return 0;
    }

    if(list->head!=NULL){
        llist_clear(list);
    }

    char c = 0;
    int cur = 0;
    int b = 0;
    int n = 1;
    while((c = fgetc(fp))!=EOF){
        if(c=='-'){
            n = n * -1;
        }
        else if((c<'0'||c>'9')&&b){
            cur/=10;
            llist_add(list,cur*n);
            b=0;
            cur = 0;
            n=1;
        }
        else{
            cur+=c-'0';
            cur*=10;
            b=1;
        }
    }
    if(b){
        cur/=10;
        llist_add(list,cur*n);
    }
	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending){
    //Should you sort linked lists by switching the value rather than the order? Part of me thinks that's a bad idea, but I don't know why.
    //And if not what's a better way to switch up the order? This way sucks.
    int sorted = 0;
    while(!sorted){
        ListNode * c = list->head;
        if(ascending){
            sorted = 1;
            if(c->value>c->next->value){
                ListNode * temp = c->next->next;
                list->head = c->next;
                list->head->next = c;
                c->next = temp;
                sorted = 0;
            }
            while(c->next->next!=NULL){
                if((c->next->value)>(c->next->next->value)){
                    ListNode * temp1 = c->next;
                    c->next = c->next->next;
                    ListNode * temp2 = c->next->next;
                    c->next->next = temp1;
                    temp1->next = temp2;
                    sorted = 0;
                }
                c = c->next;
            }
        }
        else{
            sorted = 1;
            if(c->value<c->next->value){
                ListNode * temp = c->next->next;
                list->head = c->next;
                list->head->next = c;
                c->next = temp;
                sorted = 0;
            }
            while(c->next->next!=NULL){
                if((c->next->value)<(c->next->next->value)){
                    ListNode * temp1 = c->next;
                    c->next = c->next->next;
                    ListNode * temp2 = c->next->next;
                    c->next->next = temp1;
                    temp1->next = temp2;
                    sorted = 0;
                }
                c = c->next;
            }
        }
    }

}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
    if(list->head==NULL){
        return 0;
    }
	ListNode * temp = list->head;
	*value = list->head->value;
	list->head = list->head->next;
	free(&temp->value);
    free(&temp->next);
    free(temp);
    temp = NULL;
	return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
	ListNode * c = list->head;
	if(c==NULL){
        return 0;
	}
	while (c != NULL) {
		if(c->next->next==NULL){
			ListNode * temp = c->next;
			c->next = NULL;
			*value = temp->value;
			free(&temp->value);
			free(&temp->next);
			free(temp);
            temp = NULL;
			return 1;
		}
		c = c->next;
	}
	//How the fuck will this ever happen? I'll probably find out...
    return 0;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
	ListNode * c = (ListNode *) malloc(sizeof(ListNode));
	c->value = value;

	c->next = list->head;
	list->head = c;
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
    ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	n->next = NULL;
	ListNode * c = list->head;
	if(c==NULL){
	    list->head = n;
	}
	else{
	    while(c->next!=NULL){
        	c = c->next;
	    }
	    c->next = n;
	}
}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
    ListNode * c = list->head;
    ListNode * temp;
    while(c!=NULL){
        temp = c;
        c = c->next;
        free(&temp->value);
        free(&temp->next);
        free(temp);
        temp = NULL;
    }

}
