#include <iostream>

using namespace std;

class Deque
{
	public:
		Deque();
		void enqueue_front(int);
		void enqueue_back(int);
		int dequeue_front();
		int dequeue_back();
		int get_array_size() { return size; }
		bool is_empty() { return empty; }
		void printarr(int a[], int n);
		
		
	private:
		void reallocate();
		bool is_full() { return full; }
		int nElems() { return ((size + bIndex - fIndex) % size); }
		
		int fIndex;
		int bIndex;
		int size;
		int* data;
		bool empty;
		bool full;
};