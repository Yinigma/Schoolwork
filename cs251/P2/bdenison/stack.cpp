 #include "stack.h"
 #include <utility>
 
 Stack::Stack()
 {
	 head = NULL;
	 size = 0;
 }
 
 void Stack::push(pair<int,int> p)
 {
	 node* temp = head;
	 head = new node();
	 head->next = temp;
	 head->data = p;
	 size++;
 }
 
 pair<int,int> Stack::pop()
 {
	 if (size == 0) {
		 return pair<int, int>(NULL, NULL);
	 }
	 node* temp = head;
	 head = head->next;
	 pair<int, int> p = temp->data;
	 delete temp;
	 size--;
	 return p;
 }

 pair<int, int> Stack::peek()
 {
	 if (size == 0) {
		 return pair<int, int>(NULL, NULL);
	 }
	 return head->data;
 }

 void Stack::scorchedEarth() {
	 for (int i = 0; i < size; i++) {
		 node* temp = head;
		 head = head->next;
		 delete temp;
	 }
	 if (head == NULL) {
		 size = 0;
	 }
 }