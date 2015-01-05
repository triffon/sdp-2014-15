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
	BIntTree t(1,
			BIntTree(2,
					BIntTree(3, BIntTree(), BIntTree()),
					BIntTree(4, BIntTree(), BIntTree())),
			BIntTree(5,
					BIntTree(),
					BIntTree(6, BIntTree(), BIntTree())));
	cout << t << endl;
}

int main() {
	// testTree();
	testBinaryTree();
	return 0;
}



