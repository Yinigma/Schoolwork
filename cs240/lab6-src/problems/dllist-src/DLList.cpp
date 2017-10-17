#include "DLList.h"

DLList::DLList()
{
	head = new DLNode;
	head->next = head;
	head->prev = head;
}

DLList::~DLList()
{
	delete head;
}

void DLList::print()
{
	DLNode * c = head->next;
	while(c!=head){
		std::cout<<c->data<<std::endl;
		c = c->next;
	}
}

void DLList::printSorted()
{
	bool sorted = false;
	DLList * toSort = new DLList();
	DLNode * c = head->next;
	while(c!=head){
		toSort->insertFront(c->data);
		c = c->next;
	}
	c = toSort->head->next;
	while(!sorted){
		while(c->next!=toSort->head){
			sorted = true;
			if((c->data)>(c->next->data)){
				int temp = c->data;
				c->data = c->next->data;
				c->next->data = temp;
				sorted = false;
			}
			c = c->next;
		}
	}
	
	c = toSort->head->next;
	while(c!=toSort->head){
		std::cout<<c->data<<std::endl;
		c = c->next;
	}
}

void DLList::insertFront(int data)
{
	DLNode * c = new DLNode;
	c->data = data;
	c->prev = head;
	c->next = head->next;
	head->next->prev = c;
	head->next = c;
}

void DLList::insertBack(int data)
{
	DLNode * c = new DLNode;
	c->data = data;
	c->prev = head->prev;
	c->next = head;
	head->prev->next = c;
	head->prev = c;
}

bool DLList::removeLast(int & data)
{
	data = head->prev->data;
	if(head->prev!=head){
		head->prev = head->prev->prev;
		head->prev->next = head;
		return true;
	}
	return false;
}

DLList * DLList::difference(DLList & list)
{
	DLList * diff = new DLList();
	DLNode * c = head->next;
	DLNode * d;
	bool match;
	while(c!=head){
		d = list.head->next;
		match = false;
		while(d!=list.head){
			if(c->data == d->data){
				match = true;
			}
			d = d->next;
		}
		if(!match){
			diff->insertBack(c->data);
		}
		c = c->next;
	}
	return diff;
}

DLList * DLList::getRange(int start, int end)
{
	
	return this;
}

DLList * DLList::intersection(DLList & list)
{
	DLList * inter = new DLList();
	DLNode * c = head->next;
	DLNode * d;
	DLNode * in;
	while(c!=head){
		d = list.head->next;
		while(d!=list.head){
			if(c->data == d->data){
				in = inter->head->next;
				bool inList = false;
				while(in!=inter->head){
					if(in->data==d->data){
						inList = true;
					}
					in = in->next;
				}
				if(!inList){
					inter->insertBack(d->data);
				}
			}
			d = d->next;
		}
		c= c->next;
	}
	return  inter;
}

void DLList::removeRange(int start, int end)
{

}
