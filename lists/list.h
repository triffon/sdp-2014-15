/*
 * list.h
 *
 *  Created on: 2.12.2014 г.
 *      Author: trifon
 */

#ifndef LIST_H_
#define LIST_H_

template <typename T, typename P>
class List {
public:
	// проверява дали списъкът е празен
	virtual bool empty() const = 0;

	// вмъкване преди
	virtual void insertBefore(T const&, P const&) = 0;

	// вмъкване след
	virtual void insertAfter(T const&, P const&) = 0;

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
	// Iterator<T> operator++(int);

	// if (it) ...
	// проверка за валидност
	virtual operator bool() const = 0;

	// if (!it) ...
	// проверка за невалидност
	virtual bool operator!() const {
		return !this->operator bool();
	}

	virtual ~Iterator();
};



#endif /* LIST_H_ */
