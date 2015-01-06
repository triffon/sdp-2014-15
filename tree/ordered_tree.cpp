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
private:
	TreeNode<T>*& findNode(T const& data) {
		TreeNode<T>** p = &(this->root);
		while (*p != NULL && (*p)->data != data) {
			if (data < (*p)->data)
				p = &((*p)->left);
			else
				p = &((*p)->right);
		}
		return *p;
	}

	TreeNode<T>*& findMin(TreeNode<T>*& node) const {
		TreeNode<T>** p = &node;
		while ((*p)->left != NULL)
			p = &((*p)->left);
		// (*p)->left == NULL <-> *p е указател към най-
		// малкия елемент
		return *p;
	}

public:
	/*
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
	*/

	T* search(T const& data) {
		TreeNode<T>*& p = findNode(data);
		if (p == NULL)
			return NULL;
		return &p->data;
	}

	/*
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
	*/

	bool addElement(T const& data) {
		TreeNode<T>*& p = findNode(data);
		if (p != NULL)
			return false;
		p = new TreeNode<T>(data);
		return true;
	}

	bool deleteElement(T const& data) {
		TreeNode<T>*& p = findNode(data);
		if (p == NULL)
			return false;
		if (p->left == NULL) {
			// нямаме ляво поддърво
			TreeNode<T>* q = p;
			p = p->right;
			delete q;
			return true;
		}
		if (p->right == NULL) {
			// нямаме дясно поддърво
			TreeNode<T>* q = p;
			p = p->left;
			delete q;
			return true;
		}
		// имаме и двете поддървета
		TreeNode<T>*& m = findMin(p->right);
		// m е псевдоним на указателя към минималния елемент
		// в дясното поддърво на p

		// записваме най-малкато стойност от дясното поддърво
		// на мястото на елемента, който ще изтриваме
		p->data = m->data;

		// изтриваме най-малкия елемент
		// като закачаме неговото дясно поддърво за родителя му
		TreeNode<T>*q = m;
		m = m->right;
		delete q;

		return true;
	}
};


