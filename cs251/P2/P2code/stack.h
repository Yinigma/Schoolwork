 #include <iostream>
 #include <utility>
 
 using namespace std;
 
 class Stack
 {
	 public:
		
		Stack();
		void push(pair<int,int>);
		pair<int,int> pop();
 };