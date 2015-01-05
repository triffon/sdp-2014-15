/*
 * slist.cpp
 *
 *  Created on: 5.01.2015 г.
 *      Author: trifon
 */

#include <iostream>
#include "linked_list.cpp"
using namespace std;

class SElement {
public:
	virtual void print(ostream& os = cout) = 0;
	virtual void collectInts(LinkedList<int>&) = 0;
	virtual ~SElement() {}
};

class SInt : public SElement {
private:
	int data;
public:
	SInt(int _data = 0) : data(_data) {}

	void print(ostream& os = cout) {
		os << data;
	}

	void collectInts(LinkedList<int>& l) {
		l.insertEnd(data);
	}
};

class SList : public LinkedList<SElement*>, public SElement {
public:
	void print(ostream& os = cout) {
		os << '(';
		bool first = true;
		for(LinkedListIterator<SElement*> it =
				LinkedList<SElement*>::begin(); it; ++it) {
			if (!first)
				os << ' ';
			else
				first = false;
			(*it)->print(os);
		}
		os << ')';
	}

	void collectInts(LinkedList<int>& l) {
		for(LinkedListIterator<SElement*> it =
				LinkedList<SElement*>::begin(); it; ++it)
			(*it)->collectInts(l);
	}
};
