/*
 * bintree.cpp
 *
 *  Created on: 5.01.2015 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;

template <typename T>
struct TreeNode {
	TreeNode(T const& _data = T(),
			 TreeNode* _left = NULL,
			 TreeNode* _right = NULL) : data(_data),
					 	 	 	 	    left(_left),
					 	 	 	 	    right(_right) {}
	T data;
	TreeNode *left, *right;
};

template <typename T>
class BinaryTreeIterator {
	// BinaryTree<int> t;
	// BinaryTreeIterator<int> it = t.iterator();
	// cout << *it;
	// *it = 5;
	// it++ --> връщат итератора на дясното поддърво
	// ++it --> връщат итератора на лявото поддърво
	// if (it) ...
	// if (!it) ...

private:
	TreeNode<T>* ptr;
	static T error;
public:
	BinaryTreeIterator(TreeNode<T>* _ptr = NULL) : ptr(_ptr) {}

	T& operator*() {
		if (ptr == NULL)
			return error;
		return ptr->data;
	}

	// ++it
	BinaryTreeIterator operator++() const {
		if (ptr == NULL)
			return *this;
		return BinaryTreeIterator(ptr->left);
	}

	// it++
	BinaryTreeIterator operator++(int) const {
		if (ptr == NULL)
			return *this;
		return BinaryTreeIterator(ptr->right);
	}

	operator bool() const {
		return ptr != NULL;
	}
};

template <typename T>
T BinaryTreeIterator<T>::error;

template <typename T>
class BinaryTree {
private:
	TreeNode<T>* root;
public:
	BinaryTree() : root(NULL) {}
	BinaryTree(T const& data,
			BinaryTree const& left,
			BinaryTree const& right) {
		root = new TreeNode<T>(data, left.root, right.root);
	}
	BinaryTree(BinaryTree const& bt) {}
	BinaryTree& operator=(BinaryTree const&) {
		return *this;
	}
	~BinaryTree() {}

	// !!!TreeNode<T>* getRoot() const { return root; }

	typedef BinaryTreeIterator<T> I;
	I iterator() const {
		return I(root);
	}
};

template <typename T>
ostream& operator<<(ostream& os, BinaryTree<T> const& bt) {
	return os << bt.iterator();
}

template <typename T>
ostream& operator<<(ostream& os, BinaryTreeIterator<T> it) {
	if (!it)
		return os;
	return os << '(' << *it << ',' << ++it << ',' << it++ << ')';
}
