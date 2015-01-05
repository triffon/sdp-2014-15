/*
 * tree_examples.cpp
 *
 *  Created on: 5.01.2015 г.
 *      Author: trifon
 */

#include "tree.cpp"

typedef Tree<int> IntTree;

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
}

int main() {
	testTree();
	return 0;
}



