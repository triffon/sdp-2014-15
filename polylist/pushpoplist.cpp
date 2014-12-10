/*
 * pushpoplist.cpp
 *
 *  Created on: 9.12.2014 г.
 *      Author: trifon
 */

#include <iostream>
#include "lqueue.cpp"
#include "lstack.cpp"

template <typename T>
class PushPop {
public:
	virtual bool push(T const&) = 0;
	virtual bool pop(T&) = 0;
	virtual ~PushPop() { }
};


template <typename T>
class PushPopQueue : public PushPop<T>, public LQueue<T> {
public:
	bool push(T const& x) {
		return LQueue<T>::push(x);
	}
	bool pop(T& x) {
		return LQueue<T>::pop(x);
	}

};

template <typename T>
class PushPopStack : public PushPop<T>, public LinkedStack<T> {
public:
	bool push(T const& x) {
		return LinkedStack<T>::push(x);
	}
	bool pop(T& x) {
		if (LinkedStack<T>::empty())
			return false;
		x = LinkedStack<T>::pop();
		return true;
	}
};

