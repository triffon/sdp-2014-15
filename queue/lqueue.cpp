/*
 * lqueue.cpp
 *
 *  Created on: 11.11.2014 г.
 *      Author: trifon
 */

#include <cstddef>
#include "queue.h"

template <typename T>
struct QueueElement {
	QueueElement(T const& d = T(),
			     QueueElement* n = NULL) :
		data(d), next(n) {}
	T data;
	QueueElement* next;
};

template <typename T>
class LQueue : public Queue<T> {
private:
	QueueElement<T> *front, *back;
	int size;
	void copy(LQueue const&);
	void clean();
public:
	LQueue();
	LQueue(LQueue const&);
	LQueue& operator=(LQueue const&);
	~LQueue();
	bool empty() const;
	bool push(T const&);
	T pop();
	bool pop(T&);
	T head() const;
	bool head(T&) const;
	int length() const { return size; }
};

template <typename T>
LQueue<T>::LQueue() : front(NULL), back(NULL),
					  size(0) {}

template <typename T>
bool LQueue<T>::empty() const {
	return front == NULL;
	// return back == NULL;
	// return size == 0;
}

template <typename T>
bool LQueue<T>::push(T const& x) {
	QueueElement<T>* p = new QueueElement<T>(x);
	if (!p)
		return false;
	if (empty())
		front = p;
	else
		back->next = p;
	back = p;
	size++;
	return true;
}

template <typename T>
bool LQueue<T>::pop(T& x) {
	if (!head(x))
		return false;
	QueueElement<T>* p = front;
	front = front->next;
	if (front == NULL)
		back = NULL;
	delete p;
	size--;
	return true;
}

template <typename T>
T LQueue<T>::pop() {
	T x;
	pop(x);
	return x;
}

template <typename T>
bool LQueue<T>::head(T& x) const {
	if (empty())
		return false;
	x = front->data;
	return true;
}

template <typename T>
T LQueue<T>::head() const {
	T x;
	head(x);
	return x;
}

template <typename T>
void LQueue<T>::copy(LQueue<T> const& q) {
	QueueElement<T>* toCopy = q.front;
	/*
	while (toCopy != NULL) {
		push(toCopy->data);
		toCopy = toCopy->next;
	}
	*/
	for(QueueElement<T>* toCopy = q.front;
			toCopy; toCopy = toCopy->next)
		push(toCopy->data);
}

template <typename T>
void LQueue<T>::clean() {
	T x;
	while (pop(x));
	// за домашно: директна реализация
}

template <typename T>
LQueue<T>::LQueue(LQueue<T> const& q) {
	copy(q);
}

template <typename T>
LQueue<T>& LQueue<T>::operator=(LQueue<T> const& q) {
	if (&q != this) {
		clean();
		copy(q);
	}
	return *this;
}

template <typename T>
LQueue<T>::~LQueue() {
	clean();
}
