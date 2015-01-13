/*
 * graph_examples.cpp
 *
 *  Created on: 13.01.2015 г.
 *      Author: trifon
 */

#include "graph.cpp"

typedef Graph<int> IntGraph;
typedef LinkedListIterator<int> VI;

Graph<int> sampleGraph() {
	Graph<int> g;
	for(int i = 1; i <= 6; i++)
		g.addVertex(i);
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(2, 6);
	g.addEdge(1, 3);
	g.addEdge(3, 4);
	g.addEdge(3, 6);
	g.addEdge(4, 1);
	g.addEdge(4, 5);
	g.addEdge(6, 5);
	g.addEdge(5, 3);
	return g;
}

Graph<int> fullGraph(int n) {
	Graph<int> g;
	for(int i = 1; i <= n; i++) {
		g.addVertex(i);
		for(int j = 1; j <= n - 1; j++)
			g.addEdge(i, j);
	}
	return g;
}

void printGraph(Graph<int> const& g) {
	for(int i = 1; i <= 6; i++) {
		cout << i << " -> ";
		for (VI it = g.successors(i); it; ++it)
			cout << *it << ' ';
		cout << endl;
	}
}

template <typename V>
void printDFSRec(Graph<V> const& g, V const& v, LinkedList<V>& visited) {
	cout << v << ' ';
	visited.insertEnd(v);
	for(LinkedListIterator<V> it = g.successors(v); it; ++it)
		if (!member(visited.begin(), *it))
			printDFSRec(g, *it, visited);
}

template <typename V>
void printDFS(Graph<V> const& g, V const& v) {
	LinkedList<V> l;
	printDFSRec(g, v, l);
	cout << endl;
}

template <typename V>
void printBFS(Graph<V> const& g, V const& v) {
	LinkedList<V> toVisit;
	toVisit.insertEnd(v);
	LinkedListIterator<V> it = toVisit.begin();
	while (it) {
		cout << *it << ' ';
		for(LinkedListIterator<V> sit = g.successors(*it); sit; ++sit)
			if (!member(toVisit.begin(), *sit))
				toVisit.insertEnd(*sit);
		++it;
	}
	cout << endl;
}

// O(n*m)
template <typename V>
bool findPathRec(Graph<V> const& g, V const& a, V const& b,
				 LinkedList<V>& visited, LinkedList<V>& path) {
	visited.insertEnd(a);
	path.insertEnd(a);
	if (a == b)
		return true;
	for(LinkedListIterator<V> sit = g.successors(a); sit; ++sit)
		if (!member(visited.begin(), *sit) &&
				findPathRec(g, *sit, b, visited, path))
				return true;
	V tmp;
	path.deleteEnd(tmp);
	return false;
}

template <typename V>
LinkedList<V> findPath(Graph<V> const& g, V const& a, V const& b) {
	LinkedList<V> visited, path;
	findPathRec(g, a, b, visited, path);
	return path;
}

// O(n!*n)
template <typename V>
bool findPathRec2(Graph<V> const& g, V const& a, V const& b,
				 LinkedList<V>& path) {
	path.insertEnd(a);
	if (a == b)
		return true;
	for(LinkedListIterator<V> sit = g.successors(a); sit; ++sit)
		if (!member(path.begin(), *sit) &&
				findPathRec2(g, *sit, b, path))
				return true;
	V tmp;
	path.deleteEnd(tmp);
	return false;
}

template <typename V>
LinkedList<V> findPath2(Graph<V> const& g, V const& a, V const& b) {
	LinkedList<V> path;
	findPathRec2(g, a, b, path);
	return path;
}

// O(n!*n)
template <typename V>
void findAllPathsRec(Graph<V> const& g, V const& a, V const& b,
					 LinkedList<V>& path) {
	path.insertEnd(a);
	if (a == b)
		cout << path;
	else
		for(LinkedListIterator<V> sit = g.successors(a); sit; ++sit)
			if (!member(path.begin(), *sit))
				findAllPathsRec(g, *sit, b, path);
	V tmp;
	path.deleteEnd(tmp);
}

template <typename V>
void findAllPaths(Graph<V> const& g, V const& a, V const& b) {
	LinkedList<V> path;
	findAllPathsRec(g, a, b, path);
}

int main() {
	IntGraph g = sampleGraph();
	printGraph(g);
	printDFS(g, 1);
	printBFS(g, 1);
	cout << "->" << findPath(g, 1, 5) << "<-" << endl;
	cout << "->" << findPath2(g, 1, 5) << "<-" << endl;
	findAllPaths(g, 1, 6);
	g = fullGraph(200);
	cout << "findPath:\n";
	cout << findPath(g, 1, 200);
	// !!! cout << "findPath2:\n";
	// !!! cout << findPath2(g, 1, 200);
	return 0;
}


