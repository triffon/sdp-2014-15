/*
 * ordered_tree.cpp
 *
 *  Created on: 6.01.2015 г.
 *      Author: trifon
 */

#include "bintree.cpp"

template <typename T>
// считаме, че операциите <, >, <=, >=, ==, != дефинират
// линейна наредба над T
class OrderedTree : public BinaryTree<T> {
public:
	T* search(T const& data) const {
		BinaryTreeIterator<T> it = this->iterator();
		while (it && data != *it)
			if (data < *it)
				it = ++it;
			else
				it = it++;
		// когато сме намерили data <-> data == *it
		// ИЛИ
		// когато го няма в дървото <-> !it
		if (!it)
			return NULL;
		return &*it;
	}

	bool addElement(T const& data) {
		TreeNode<T>* p = this->root;
		if (this->root == NULL) {
			this->root = new TreeNode<T>(data);
			return true;
		} else
		while (p->data != data)
			if (data < p->data)
				if (p->left == NULL) {
					p->left = new TreeNode<T>(data);
					return true;
				}
				else
					p = p->left;
			else
				// data > p->data
				if (p->right == NULL) {
					p->right = new TreeNode<T>(data);
					return true;
				}
				else
					p = p->right;
		// когато сме намерили мястото на data и там няма нищо
		// (тогава вмъкваме)
		// p == NULL
		// ИЛИ
		// когато сме намерили data (тогава грешка)
		// p->data == data
		return false;
	}
};


