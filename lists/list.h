/*
 * list.h
 *
 *  Created on: 2.12.2014 г.
 *      Author: trifon
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
using namespace std;

template <typename T, typename P>
class List {
protected:
	void copy(List const& l) {
		// за всеки елемент от l
		// да го добавим в *this
		// допускаме, че *this е празен
		for(P it = l.begin(); it; ++it)
			insertEnd(*it);
	}

	void clean() {
		T tmp;
		while (!empty())
			deleteBegin(tmp);
	}

public:
	// проверява дали списъкът е празен
	virtual bool empty() const = 0;

	// вмъкване преди
	virtual bool insertBefore(T const&, P const&) = 0;

	// вмъкване след
	virtual bool insertAfter(T const&, P const&) = 0;

	// изтриване преди
	virtual bool deleteBefore(T&, P const&) = 0;

	// изтриване след
	virtual bool deleteAfter(T&, P const&) = 0;

	// изтриване на
	virtual bool deleteAt(T&, P&) = 0;

	// достъп до елемент
	// virtual T& getAt(P const&) = 0;

	// позиция в началото
	virtual P begin() const = 0;

	// позиция в края
	virtual P end() const = 0;

	// добавяне в началото
	bool insertBegin(T const& x) {
		return insertBefore(x, begin());
	}

	// добавяне в края
	bool insertEnd(T const& x) {
		return insertAfter(x, end());
	}

	// изтриване в началото
	bool deleteBegin(T& x) {
		P it = begin();
		return deleteAt(x, it);
	}

	// изтриване в края
	bool deleteEnd(T& x) {
		return deleteAt(x, end());
	}

	// виртуален деструктор
	virtual ~List() {}
};

template <typename T>
class Iterator {
public:
	/*
	 * List<T> l;
	 * Iterator<T> it = l.begin();
	 * Iterator<T> it = l.end();
	 * cout << *it << endl;
	 * if (it)
	 * 	  *it = 5;
	 * it++;
	 * if (!it)
	 * 	  cout << "Невалидна позиция" << endl;
	 */

	// достъп до елемент
	virtual T& operator*() = 0; // const?

	// преминаване на следваща позиция
	// ++it
	virtual Iterator<T>& operator++() = 0;

	// it++;
	// некоректно, понеже Iterator<T> е абстрактен!!!!
	// не можем да върнем обект Iterator<T>!
	// Iterator<T> operator++(int);

	// if (it) ...
	// проверка за валидност
	virtual operator bool() const = 0;

	virtual ~Iterator() {}
};

template <typename T, typename P>
ostream& operator<<(ostream& os, List<T, P> const& l) {
	for(P it = l.begin(); it; ++it)
		os << *it << ' ';
	return os << endl;
}

#endif /* LIST_H_ */
