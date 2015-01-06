/*
 * tree_examples.cpp
 *
 *  Created on: 5.01.2015 г.
 *      Author: trifon
 */

#include "tree.cpp"
#include "bintree.cpp"

typedef Tree<int> IntTree;
typedef BinaryTree<int> BIntTree;

template <typename T>
void printLevel(Tree<T> const& t, int k) {
	if (k < 1)
		return;
	if (k == 1)
		cout << *t << ' ';
	else
		for(typename Tree<T>::I it = t.children(); it; ++it)
			printLevel(*it, k - 1);
}

void testTree() {
	IntTree t(0);
	t.addChild(IntTree(1)
			.addChild(IntTree(11))
			.addChild(IntTree(12)))
	 .addChild(IntTree(2))
	 .addChild(IntTree(3)
			.addChild(IntTree(31))
			.addChild(IntTree(32))
			.addChild(IntTree(33)));
	cout << t;
	printLevel(t, 1);cout << endl;
	printLevel(t, 2);cout << endl;
	printLevel(t, 3);cout << endl;
}

void testBinaryTree() {
	BIntTree empty;
	BIntTree t4(4, empty, empty);
	BIntTree t3(3, empty, empty);
	BIntTree t6(6, empty, empty);
	BIntTree t2(2, t3, t4);
	BIntTree t5(5, empty, t6);
	BIntTree t(1, t2, t5);
	cout << t << endl;
}

int main() {
	// testTree();
	testBinaryTree();
	return 0;
}



