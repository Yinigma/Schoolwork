#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include <algorithm>
#include <type_traits>
#include <stdlib.h>
#include <string.h>

/**
 * ArrayList class
 *
 * This class implements an ArrayList in a fashion
 * that is similar to that of Java, but also adds
 * a lot of useful C++ features.
 *
 * @author Hunter Allen <allen286@purdue.edu>
 * @author Brian Hays <hays1@purdue.edu>
 */
template<class T>
class ArrayList
{
public:
	ArrayList();

	int indexOf(const T& other);
	int indexOf(const T& object, int occurrence);
	int lastIndexOf(const T& other);
	const int & size(){ return m_size; }
	const int & capacity(){ return m_capacity; }
	const T & get(int index){ return pElements[index]; }
	const T remove(int index);
	void remove(const T & toRemove, bool * ok);
	inline T & operator [](int index){ return pElements[index]; }

	void print();

	void add(const T& toPush);
	void add(const T& toPush, int index);
	void push_back(const T& toPush);
	void push_front(const T& toPush);

	void clear();

	bool isEmpty(){ return m_size == 0; }
	bool contains(const T& object);

	void sort();
	
	/**
	 * @brief      Gets operator.
	 * 
	 * Deep copies the other ArrayList.
	 * 
	 * @param[in]  other  ArrayList to copy
	 *
	 * @return     return *this
	 */
	ArrayList<T> & operator = (const ArrayList<T> & other)
	{
		/**
		 * @todo Implement the = operator.
		 * Make a deep copy of other and set
		 * *this equal to it.
		 */

		T * temp = new T[other.size()];
		
		for(int i = 0; i<other.size(); i++){
			temp[i] = other[i];
		}
		delete pElements;
		pElements = temp;
		m_size = other.size();
		m_capacity = other.capcatiy();
		return *this;
	}

	/**
	 * @brief      Equals operator.
	 *
	 * @param      other  Array with which we are checking equality.
	 *
	 * @return     True, if they are equal. :P
	 */
	bool operator == (ArrayList<T> & other)
	{
		/**
		 * @todo Implement the == operator.
		 */

		if(m_size==other.size()){
			for(int i = 0; i<m_size; i++){
				if(pElements[i]!=other[i]){
					return false;
				}
			}
			return true;
		}
		return false;
	}

	/**
	 * @brief      Overloads the input operator.
	 *
	 * The input element shall be added to the back of the array.
	 * 
	 * @param[in]  toAdd  Adds an element to the array.
	 *
	 * @return     *this
	 */
	ArrayList<T> & operator << (const T & toAdd) {
		
		add(toAdd);

		return *this;
	}

	/**
	 * @brief      Overloads the input operator.
	 * 
	 * The list shall be appended to this one.
	 *
	 * @param      other  List to adjoin.
	 *
	 * @return     *this
	 */
	ArrayList<T> & operator << (ArrayList<T> & other) {
		
		int size = other.size();
		for(int i = 0; i<size; i++){
			add(other[i]);
		}

		return *this;
	}

	/**
	 * @brief      Overloads += operator.
	 *
	 * This adds another element to the list, just like <<.
	 * 
	 * @param[in]  toAdd  Adds an element to the end.
	 *
	 * @return     *this
	 */
	ArrayList<T> & operator += (const T & toAdd) {
		/**
		 * @todo This should be the same as <<
		 */

		add(toAdd);

		return *this;
	}

	/**
	 * @brief      Overloads += operator.
	 *
	 * Another one of 'dem add to back things.
	 * 
	 * @param      other  The list you are to adjoin.
	 *
	 * @return     *this
	 */
	ArrayList<T> & operator += (ArrayList<T> & other) {
		/**
		 * @todo Analogously, this does the same as <<.
		 */

		int size = other.size();
		for(int i = 0; i<size; i++){
			add(other[i]);
		}

		return *this;
	}

private:
	T * pElements;
	int m_size;
	int m_capacity;
	const static int SIZE_INCREMENT = 2;
};
#endif
