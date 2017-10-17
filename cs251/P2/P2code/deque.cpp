#include <iostream>
#include "deque.h"

using namespace std;

Deque::Deque()
{
	//TODO: Write the Deque constructor
	//NOTE: Start with an array of size 10!
}

void Deque::enqueue_front(int n)
{
	//TODO: Front enqueue method
}

void Deque::enqueue_back(int n)
{
	//TODO: Back enqueue
}

int Deque::dequeue_front()
{
	//TODO: front dequeue
	return 0;
}

int Deque::dequeue_back()
{
	//TODO: back dequeue
	return 0;
}

bool Deque::is_full()
{
	//TODO: Determine if you need to double the array
	return false;
}

void Deque::reallocate()
{
	//TODO: Correctly reallocate memory for the deque. Use the doubling strategy.
}