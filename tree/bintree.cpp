/*
 * bintree.cpp
 *
 *  Created on: 5.01.2015 г.
 *      Author: trifon
 */

#ifndef __BINTREE_CPP
#define __BINTREE_CPP

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
protected:
	TreeNode<T>* root;
private:
	void deleteNode(TreeNode<T>* node) {
		if (node != NULL) {
			deleteNode(node->left);
			deleteNode(node->right);
			delete node;
		}
	}

	TreeNode<T>* copyNode(TreeNode<T>* src) {
		if (src == NULL)
			return NULL;
		return new TreeNode<T>(src->data,
							copyNode(src->left),
							copyNode(src->right));
	}

	void adoptLeft(TreeNode<T>*& node) {
		adopt(root->left, node);
	}

	void adoptRight(TreeNode<T>*& node) {
		adopt(root->right, node);
	}

	void adopt(TreeNode<T>*& newNode, TreeNode<T>*& oldNode) {
		newNode = oldNode;
		oldNode = NULL;
	}

public:
	BinaryTree() : root(NULL) {}
	BinaryTree(T const& data) : root(new TreeNode<T>(data))
	{}
	BinaryTree(T const& data,
			BinaryTree& left,
			BinaryTree& right) {
		root = new TreeNode<T>(data);
		adoptLeft(left.root);
		adoptRight(right.root);
	}

	BinaryTree(BinaryTree const& bt) {
		root = copyNode(bt.root);
	}

	BinaryTree& operator=(BinaryTree const& bt) {
		if (this != &bt) {
			deleteNode(root);
			root = copyNode(bt.root);
		}
		return *this;
	}

	~BinaryTree() {
		deleteNode(root);
	}

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

#endif
