/*
 * linked_list.cpp
 *
 *  Created on: 2.12.2014 г.
 *      Author: trifon
 */

#include "list.h"
#include <cstddef>

template <typename T>
struct ListElement {
	T data;
	ListElement* next;

	ListElement(T const& _data = T(),
			    ListElement* _next = NULL) :
		data(_data), next(_next) {}
};

template <typename T>
class LinkedList;

template <typename T>
class LinkedListIterator : public Iterator<T> {
private:
	ListElement<T>* ptr;

	friend class LinkedList<T>;

	static T error;
public:
	LinkedListIterator(ListElement<T>* _ptr = NULL) :
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
	LinkedListIterator<T> operator++(int) {
		ListElement<T>* oldptr = ptr;
		++(*this);
		return oldptr;
	}

	// проверка за валидност
	operator bool() const {
		return ptr != NULL;
	}

	~LinkedListIterator() {}
};

template <typename T>
T LinkedListIterator<T>::error;

template <typename T>
class LinkedList :
		public List<T, LinkedListIterator<T> > {
private:

	typedef LinkedListIterator<T> I;

	ListElement<T> *front, *back;

	// намиране на предишната позиция
	// O(n)
	I findPrevious(I const& it) {
		if (!it)
			// даден ни е невалиден итератор
			// връщаме им го обратно :)
			return it;
		I prev = begin();
		while (prev && prev.ptr->next != it.ptr)
			++prev;
		// !prev || prev.ptr->next == it.ptr
		return prev;
	}

public:
	LinkedList() : front(NULL), back(NULL) {}

	LinkedList(LinkedList const& l) : front(NULL), back(NULL) {
		this->copy(l);
	}

	LinkedList& operator=(LinkedList const& l) {
		if (&l != this) {
			this->clean();
			this->copy(l);
		}
		return *this;
	}

	~LinkedList() {
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

	// вмъкване преди
	// O(n)
	bool insertBefore(T const& x, I const& it) {
		if (!it) {
			if (empty())
				return insertAfter(x, it);
			else
				return false;
		}
		// it е валиден
		if (it.ptr == front) {
			front = new ListElement<T>(x, front);
			return true;
		} else {
			I prev = findPrevious(it);
			return insertAfter(x, prev);
		}
	}

	// вмъкване след
	// O(1)
	bool insertAfter(T const& x, I const& it) {
		if (!it)
			if (empty())
				// включваме първи елемент в празен списък
				front = back = new ListElement<T>(x);
			else
				return false;
		else {
			it.ptr->next = new ListElement<T>(x, it.ptr->next);
			// дали вмъкваме след последния елемент?
			if (back->next != NULL)
				back = back->next;
		}
		return true;
	}

	// изтриване преди
	// O(n)
	bool deleteBefore(T& x, I const& it) {
		if (!it)
			// невалидна позиция
			return false;

		I prev = findPrevious(it);
		return deleteAt(x, prev);
	}

	// изтриване след
	// O(1)
	bool deleteAfter(T& x, I const& it) {
		// невалидна позиция
		if (!it)
			return false;

		ListElement<T>* toDelete = it.ptr->next;

		// няма следваща позиция
		if (toDelete == NULL)
			return false;

		// изтриваме елемента на последната позиция
		if (toDelete == back)
			back = it.ptr;

		it.ptr->next = toDelete->next;
		x = toDelete->data;
		delete toDelete;
		return true;
	}

	// изтриване на
	// O(n)
	bool deleteAt(T& x, I& it) {
		if (!it)
			// невалидна позиция
			return false;

		if (it.ptr == front) {
			// изтриваме първи елемент
			ListElement<T>* toDelete = front;
			x = front->data;
			front = front->next;
			delete toDelete;
			// дали това беше последният елемент?
			if (front == NULL)
				back = NULL;
			// инвалидираме итератора
			it.ptr = NULL;
			return true;
		}

		I prev = findPrevious(it);
		// инвалидираме итератора
		it.ptr = NULL;
		return deleteAfter(x, prev);
	}

};
