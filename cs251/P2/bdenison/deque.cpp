#include <iostream>
#include "deque.h"

using namespace std;

Deque::Deque()
{
	size = 10;
	data = new int[size];
	fIndex = 0;
	bIndex = 0;
	empty = false;
	full = false;
}

void Deque::enqueue_back(int n)
{
	if (is_full()) {
		reallocate();
	}
	data[bIndex] = n;
	if (++bIndex == size) {
		bIndex = 0;
	}
	if (bIndex == fIndex) {
		full = true;
	}
	empty = false;

}

void Deque::enqueue_front(int n)
{
	if (is_full()) {
		reallocate();
	}
	if (fIndex == 0) {
		fIndex = size;
	}

	data[--fIndex] = n;
	if (bIndex == fIndex) {
		full = true;
	}
	empty = false;
}

int Deque::dequeue_back()
{
	if (empty) {
		return -1;
	}
	else {
		if (bIndex == 0) {
			bIndex = size;
		}
		int get = data[--bIndex];
		if (fIndex == bIndex) {
			empty = true;
		}
		full = false;
		return get;
	}
}

int Deque::dequeue_front()
{
	if (empty) {
		return -1;
	}
	else {
		int get = data[fIndex];
		if (++fIndex == size) {
			fIndex = 0;
		}
		if (fIndex == bIndex) {
			empty = true;
		}
		full = false;
		return get;
	}
}

void Deque::reallocate()
{
	
	//if (is_full()) {
		int* temp = data;
		data = new int[2 * size];
		for (int i = fIndex; i < size; i++) {
			data[i-fIndex] = temp[i];
		}
		for (int i = 0; i < bIndex; i++) {
			data[size-fIndex+i] = temp[i];
		}
		bIndex = size;
		fIndex = 0;
		size *= 2;
		delete temp;
	//}
	//Whoops
	/*if ((size/nElems())>=4){
		cout << "Realloc-" << endl;
		int* temp = data;
		int e = nElems();
		data = new int[size/2];
		if (bIndex > fIndex) {
			for (int i = fIndex; i < bIndex; i++) {
				data[i-fIndex] = temp[i];
			}
		}
		else if(bIndex<fIndex){
			for (int i = fIndex; i < size; i++) {
				data[i - fIndex] = temp[i];
			}
			for (int i = 0; i < bIndex; i++) {
				data[size-fIndex+i] = temp[i];
			}
		}
		bIndex = e;
		fIndex = 0;
		size /= 2;
		delete temp;
	}*/
	//Weird that doing the shit I was told in class would yield me the wrong answer.
}
void Deque::printarr(int a[],int n) {
	for (int i = 0; i < n; i++) {
		if (a[i] > -1000) {
			cout << a[i];
		}
		else {
			cout << "nil";
		}
		if (i < n - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}