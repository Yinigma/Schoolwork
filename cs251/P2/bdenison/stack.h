 #include <iostream>
 #include <utility>
 
 using namespace std;
 
 struct node {
	 node* next;
	 pair<int, int> data;
 };

 class Stack
 {
	 public:
		
		Stack();
		void push(pair<int,int>);
		pair<int,int> pop();
		pair<int, int> peek();
		bool isEmpty(){ return (size == 0); }
		void scorchedEarth();
		int getSize() { return size; }

	private:

		node * head;
		int size;
 };