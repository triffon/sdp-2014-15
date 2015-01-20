/*
 * graph.cpp
 *
 *  Created on: 13.01.2015 г.
 *      Author: trifon
 */

#include "linked_list.cpp"

template <typename T>
bool member(LinkedListIterator<T> it, T const& x) {
	while (it && *it != x)
		++it;
	return it;
}

template <typename T>
bool member(LinkedList<T> const& l, T const& x) {
	return member(l.begin(), x);
}

template <typename V>
class Graph {
private:
	typedef LinkedListIterator<V> VI;
	typedef LinkedListIterator<LinkedList<V> > SI;
	LinkedList<LinkedList<V> > graph;

	LinkedList<V>* findSuccessorsList(V const& v) {
		for(SI sit = graph.begin(); sit; ++sit)
			if (*(*sit).begin() == v)
				return &*sit;
		return NULL;
	}

	LinkedList<V> const* findSuccessorsList(V const& v) const {
		for(SI sit = graph.begin(); sit; ++sit)
			if (*(*sit).begin() == v)
				return &*sit;
		return NULL;
	}

public:

	LinkedList<V> vertices() const {
		LinkedList<V> v;
		for(SI sit = graph.begin(); sit; ++sit)
			v.insertEnd(*(*sit).begin());
		return v;
	}

	VI successors(V const& v) const {
		LinkedList<V> const* sl = findSuccessorsList(v);
		if (sl == NULL)
			return VI();
		VI it = sl->begin();
		++it;
		return it;
	}

	bool isEdge(V const& a, V const& b) const {
		return member(successors(a), b);
	}

	// Не правим проверка за коректност!
	void addVertex(V const& v) {
		LinkedList<V> sl;
		sl.insertEnd(v);
		graph.insertEnd(sl);
	}

	// Не правим проверка за коректност!
	void addEdge(V const& a, V const& b) {
		LinkedList<V>* sl = findSuccessorsList(a);
		if (sl != NULL)
			sl->insertEnd(b);
	}

	void removeEdge(V const& a, V const& b) {
		LinkedList<V>* sl = findSuccessorsList(a);
		V tmp;
		if (sl != NULL) {
			VI it = sl->begin(), prev = it;
			++it;
			for(; it; ++it, ++prev)
				if (*it == b)
					sl->deleteAfter(tmp, prev);
		}
	}

	void removeVertex(V const& v) {
		// изтриваме входящите ребра
		for(VI it = succesors(v); it; ++it)
			removeEdge(*it, v);
		// vзтриваме самия списък от наследници за v
		LinkedList<V> tmp;
		for(SI sit = graph.begin(); sit; ++sit)
			if (*(*sit).begin() == v)
				graph.deleteAt(tmp, sit);
	}
};

