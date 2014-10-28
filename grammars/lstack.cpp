/*
 * lstack.cpp
 *
 *  Created on: 21.03.2014
 *      Author: trifon
 */

#ifndef LSTACK_CPP_
#define LSTACK_CPP_

#include <cstddef>

template <typename T>
struct StackElement {
	T data;
	StackElement* next;
};

template <typename T>
class LinkedStack {
protected:
	StackElement<T>* top;
			  //  самият стек, т.е. указател към
			  // последния включен в стека елемент
public:

	LinkedStack(); // create
	LinkedStack(LinkedStack const&);

	// проверка дали стек е празен
	bool empty() const;

	// включване на нов елемент
	bool push(T const&);

	// изключване на елемент
	T pop();

	// връщане на върха на стека
	T last() const;

	// деструктор
	~LinkedStack();

	// операция за присвояване
	LinkedStack& operator=(LinkedStack const&);

private:

	// копиране
	void copy(LinkedStack const&);

	// изчистване
	void clean();
};

template <typename T>
LinkedStack<T>::LinkedStack() {
	top = NULL;
}

template <typename T>
LinkedStack<T>::LinkedStack(LinkedStack<T> const& ls) {
	copy(ls);
}

template <typename T>
void LinkedStack<T>::copy(LinkedStack<T> const& ls) {
	/* !!! неправилно !!!
	top = NULL;
	while(!ls.empty())
		push(ls.pop());
		*/
	if (ls.empty())
		top = NULL;
	else {
		// първа стъпка
		top = new StackElement<T>;
		top->data = ls.top->data;

		// подготовка за втората стъпка
		StackElement<T>* toCopy = ls.top->next;
		StackElement<T>* lastCopy = top;

		while (toCopy != NULL) {
			// копиране
			StackElement<T>* newCopy = new StackElement<T>;
			newCopy->data = toCopy->data;

			// завързване
			lastCopy->next = newCopy;

			// подготовка за следващата стъпка
			toCopy = toCopy->next;
			lastCopy = newCopy;
		}
		// затваряме веригата
		lastCopy->next = NULL;
	}
}

template <typename T>
bool LinkedStack<T>::empty() const {
	return top == NULL;
}

template <typename T>
bool LinkedStack<T>::push(T const& x) {
	StackElement<T>* el = new StackElement<T>;
	el->data = x;
	el->next = top;
	top = el;
	return true;
}

template <typename T>
T LinkedStack<T>::last() const {
	if (empty())
		return T();
	return top->data;
}

template <typename T>
T LinkedStack<T>::pop() {
	if (empty())
		return T();
	// top != NULL
	StackElement<T>* el = top;
	top = top->next;
	T x = el->data;
	delete el;
	return x;
}

template <typename T>
LinkedStack<T>::~LinkedStack() {
	clean();
}

template <typename T>
void LinkedStack<T>::clean() {
	// !!! delete top; // не е достатъчно!
	while (!empty())
		pop();
	// за домашно: директна реализация
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator =(LinkedStack<T> const& ls) {
	if (this != &ls) {
		clean();
		copy(ls);
	}
	return *this;
}

#endif /* STACK_CPP_ */
