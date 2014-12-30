/*
 * squeue.cpp
 *
 *  Created on: 11.11.2014 г.
 *      Author: trifon
 */

#include "queue.h"

int const MAX_SIZE = 100;

template <typename T>
class SQueue : public Queue<T> {
private:
	T arr[MAX_SIZE];
	int front, back, size;
	bool full() const;
public:
	SQueue();
	bool empty() const;
	bool push(T const&);
	T pop();
	bool pop(T&);
	T head() const;
	bool head(T&) const;
	int length() const { return size; }
};

template <typename T>
SQueue<T>::SQueue() : front(0), back(0), size(0) {}

template <typename T>
bool SQueue<T>::empty() const {
	return size == 0;
}

template <typename T>
bool SQueue<T>::full() const {
	return size == MAX_SIZE;
}

template <typename T>
bool SQueue<T>::push(T const& x) {
	if (full())
		return false;
	arr[back] = x;
	(++back) %= MAX_SIZE;
	size++;
	return true;
}

template <typename T>
T SQueue<T>::pop() {
	if (empty())
		return T();
	T x = head();
	(++front) %= MAX_SIZE;
	size--;
	// front++; if (front == MAX_SIZE) front = 0;
	return x;
}

template <typename T>
bool SQueue<T>::pop(T& x) {
	if (empty())
		return false;
	x = pop();
	return true;
}

template <typename T>
bool SQueue<T>::head(T& x) const {
	if (empty())
		return false;
	x = arr[front];
	return true;
}

template <typename T>
T SQueue<T>::head() const {
	T x;
	head(x);
	return x;
}
