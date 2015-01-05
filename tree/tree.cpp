/*
 * tree.cpp
 *
 *  Created on: 5.01.2015 г.
 *      Author: trifon
 */

#include <iostream>
#include "linked_list.cpp"
using namespace std;

struct Employee {
	char name[100];
	Employee* boss;
};

template <typename T>
class Tree {
private:
	T root;
// !!!	Tree<T> tree;
	LinkedList<Tree<T> > subtrees;
public:
	typedef LinkedListIterator<Tree<T> > I;

	Tree(T const& _root = T()) : root(_root) {}

	T& operator*() {
		return root;
	}

	T const& operator*() const {
		return root;
	}

	I children() const {
		return subtrees.begin();
	}

	Tree<T>& addChild(Tree<T> const& child) {
		subtrees.insertEnd(child);
		return *this;
	}
};

template <typename T>
ostream& operator<<(ostream& os, Tree<T> const& t) {
	os << '(';
	os << *t;
	for(typename Tree<T>::I it = t.children(); it; ++it)
		os << *it;
	return os << ')';
}
