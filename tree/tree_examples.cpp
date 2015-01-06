/*
 * tree_examples.cpp
 *
 *  Created on: 5.01.2015 г.
 *      Author: trifon
 */

#include "tree.cpp"
#include "bintree.cpp"
#include "lstack.cpp"

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

template <typename T>
int depth(BinaryTreeIterator<T> it) {
	if (!it)
		return 0;
	return 1 + max(depth(++it), depth(it++));
}

int priority(char op) {
	switch (op) {
	case '+':
	case '-':return 1;
	case '*':
	case '/':return 2;
	default:return -1;
	}
}

void createTree(LinkedStack<BinaryTree<char> >& rstack, char op) {
	BinaryTree<char> rtree = rstack.pop();
	BinaryTree<char> ltree = rstack.pop();
	rstack.push(BinaryTree<char>(op, ltree, rtree));
}

BinaryTree<char> createExpressionTree(char const* expr) {
	LinkedStack<char> opstack;
	LinkedStack<BinaryTree<char> > rstack;

	while(*expr) {
		if (*expr >= '0' && *expr <= '9')
			rstack.push(BinaryTree<char>(*expr));
		else
		if (*expr == '(')
			opstack.push(*expr);
		else
		if (*expr == ')') {
			char op = opstack.pop();
			while (op != '(') {
				createTree(rstack, op);
				op = opstack.pop();
			}
		} else {
			// *expr е операция
			// първо: вадим всички операции
			// с по-висок или равен приоритет
			while (!opstack.empty() &&
				   priority(opstack.last()) >=
				   priority(*expr))
				createTree(rstack,opstack.pop());
			opstack.push(*expr);
		}
		expr++;
	}
	while (!opstack.empty())
		createTree(rstack, opstack.pop());

	return rstack.pop();
}

double calculate(BinaryTreeIterator<char> it) {
	if (*it >= '0' && *it <= '9')
		// листо
		return *it - '0';
	switch (*it) {
	case '+': return calculate(++it) + calculate(it++);
	case '-': return calculate(++it) - calculate(it++);
	case '*': return calculate(++it) * calculate(it++);
	case '/': return calculate(++it) / calculate(it++);
	default: return 0;
	}
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
	cout << "Depth: " << depth(t.iterator()) << endl;
}

int const MAX = 100;

void testExpressionTree() {
	char expr[MAX];
	cin.getline(expr, MAX);
	BinaryTree<char> t = createExpressionTree(expr);
	cout << t << endl;
	cout << calculate(t.iterator()) << endl;
}

int main() {
	// testTree();
	// testBinaryTree();
	testExpressionTree();
	return 0;
}



