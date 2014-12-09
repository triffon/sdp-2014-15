/*
 * double_linked_list.cpp
 *
 *  Created on: 9.12.2014 г.
 *      Author: trifon
 */

#include "list.h"
#include <cstddef>

template <typename T>
struct DoubleListElement {
	T data;
	DoubleListElement *next, *prev;

	DoubleListElement(T const& _data = T(),
					  DoubleListElement* _next = NULL,
					  DoubleListElement* _prev = NULL) :
						  data(_data), next(_next), prev(_prev)
	{}
};

template <typename T>
class DoubleLinkedList;

template <typename T>
class DoubleLinkedListIterator : public Iterator<T> {
private:
	DoubleListElement<T>* ptr;

	friend class DoubleLinkedList<T>;

	static T error;

public:
	DoubleLinkedListIterator(DoubleListElement<T>* _ptr = NULL) :
		ptr(_ptr) {}

	T& operator*() {
		if (ptr != NULL)
			return ptr->data;
		return error;
	}

	// ++it
	Iterator<T>& operator++() {
		if (ptr != NULL)
			ptr = ptr->next;
		return *this;
	}

	// it++
	DoubleLinkedListIterator<T> operator++(int) {
		DoubleListElement<T>* oldptr = ptr;
		++(*this);
		return oldptr;
	}

	// --it
	Iterator<T>& operator--() {
		if (ptr != NULL)
			ptr = ptr->prev;
		return *this;
	}

	// it--
	DoubleLinkedListIterator<T> operator--(int) {
		DoubleListElement<T>* oldptr = ptr;
		++(*this);
		return oldptr;
	}

	// проверка за валидност
	operator bool() const {
		return ptr != NULL;
	}

	~DoubleLinkedListIterator() {}
};

template <typename T>
T DoubleLinkedListIterator<T>::error;

template <typename T>
class DoubleLinkedList : public List<T, DoubleLinkedListIterator<T> > {
private:

	typedef DoubleLinkedListIterator<T> I;

	DoubleListElement<T> *front, *back;

public:

	DoubleLinkedList() : front(NULL), back(NULL) {}

	DoubleLinkedList(DoubleLinkedList const& l) : front(NULL), back(NULL) {
		this->copy(l);
	}

	DoubleLinkedList& operator=(DoubleLinkedList const& l) {
		if (&l != this) {
			this->clean();
			this->copy(l);
		}
		return *this;
	}

	~DoubleLinkedList() {
		this->clean();
	}

	bool empty() const {
		return front == NULL;
	}

	I begin() const {
		return I(front);
	}

	I end() const {
		return I(back);
	}

	// сложност: O(1)
	bool insertAfter(T const& x, I const& it) {
		if (!it)
			if (empty())
				front = back = new DoubleListElement<T>(x);
			else
				return false;
		else {
			// it е валидна позиция
			DoubleListElement<T>* p = new DoubleListElement<T>(x, it.ptr->next, it.ptr);
			if (p->next != NULL)
				p->next->prev = p;
			else
				// след последния елемент
				back = p;
			it.ptr->next = p;
		}
		return true;
	}

	// O(1)
	bool insertBefore(T const& x, I const& it) {
		if (!it)
			if (empty())
				back = front = new DoubleListElement<T>(x);
			else
				return false;
		else {
			// it е валидна позиция
			DoubleListElement<T>* p = new DoubleListElement<T>(x, it.ptr, it.ptr->prev);
			if (p->prev != NULL)
				p->prev->next = p;
			else
				// преди първия елемент
				front = p;
			it.ptr->prev = p;
		}
		return true;
	}

	// O(1)
	bool deleteAt(T& x, I& it) {
		if (!it)
			return false;
		if (it.ptr->next != NULL)
			it.ptr->next->prev = it.ptr->prev;
		else
			// изтриваме последния елемент
			back = it.ptr->prev;

		if (it.ptr->prev != NULL)
			it.ptr->prev->next = it.ptr->next;
		else
			// изтриваме първия елемент
			front = it.ptr->next;

		x = *it;
		delete it.ptr;
		it.ptr = NULL;
		return true;
	}

	// O(1)
	bool deleteBefore(T& x, I const& it) {
		if (!it)
			return false;
		I itprev = it;
		--itprev;
		return deleteAt(x, itprev);
	}

	// O(1)
	bool deleteAfter(T& x, I const& it) {
		if (!it)
			return false;
		I itnext = it;
		++itnext;
		return deleteAt(x, itnext);
	}

};
