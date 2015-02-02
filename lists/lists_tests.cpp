/*
 * lists_tests.cpp
 *
 *  Created on: 2.12.2014 г.
 *      Author: trifon
 */

#include "linked_list.cpp"
#include "double_linked_list.cpp"

typedef DoubleLinkedList<int> TestList;
typedef DoubleLinkedListIterator<int> TestIterator;

void testLinkedList() {
	TestList l;
	for(int i = 1; i <= 5; i++) {
		l.insertEnd(i);
		l.insertBegin(i);
	}
	cout << l;
	for(TestIterator it = l.begin(); it; ++it) {
		if (*it % 2 == 0) {
			l.insertAfter(*it * 5 + 1, it);
			l.insertBefore(*it * 10, it);
		}
	}
	cout << l;
	for(TestIterator it = l.begin(); it; ++it) {
		if (*it % 5 == 0) {
			int x;
			l.deleteAfter(x, it);
			cout << "Изтрихме " << x << endl;
		} else
			if (*it % 3 == 0) {
				int x;
				l.deleteBefore(x, it);
				cout << "Изтрихме " << x << endl;
			}
	}
}

// конкатенация на l2 след l1, резултатът е в l1
template <typename T, typename I>
void concatenate(List<T, I>& l1, List<T, I> const& l2) {
	for(I it = l2.begin(); it; ++it)
		l1.insertEnd(*it);
}

void testConcatenate() {
	TestList l1, l2;
	int i = 1;
	for(; i <= 10; i++)
		l1.insertEnd(i);
	for(; i <= 20; i++)
		l2.insertEnd(i);

	concatenate(l1, l2);
	cout << l1;

}

template <typename T, typename I>
void reverse(List<T, I>& l) {
	T x;
	I it = l.begin();
	while(l.deleteAfter(x, it))
		l.insertBegin(x);
}

void testReverse() {
	TestList l;
	for(int i = 1; i <= 10; i++)
		l.insertEnd(i);
	reverse(l);
	cout << l;
}

// разделяме l на две приблизително равни по дължина части
// l1 и l2
template <typename T, typename I>
void split(List<T, I> const& l,
		   List<T, I>& l1, List<T, I>& l2) {
	I it = l.begin();
	while (it) {
		l1.insertEnd(*it++);
		if (it)
			l2.insertEnd(*it++);
	}
}

template <typename T, typename I>
void merge(List<T, I>& l,
		   List<T, I> const& l1, List<T, I> const& l2) {
	I it1 = l1.begin(), it2 = l2.begin();
	while (it1 && it2)
		if (*it1 < *it2)
			l.insertEnd(*it1++);
		else
			l.insertEnd(*it2++);
	// !it1 || !it2
	while(it1)
		l.insertEnd(*it1++);
	while(it2)
		l.insertEnd(*it2++);
}

void mergeSort(TestList& l) {
	// 1. разделяне на два подсписъка
	TestList l1, l2;
	split(l, l1, l2);

	// дъно
	if (l1.empty() || l2.empty())
		return;

	/*
	cout << "След разделянето " << endl;
	cout << l1 << ' ' << l2;
	*/

	// 2. рекурсивно сортиране
	mergeSort(l1);
	mergeSort(l2);

	/*
	cout << "Преди сливането" << endl;
	cout << l1 << ' ' << l2;
	*/

	// 3. сливане
	l.clean();
	merge(l, l1, l2);

	/*
	cout << "След сливането" << endl;
	cout << l << endl;
	*/
}

void testMergeSort() {
	TestList l;
	for(int i = 1; i <= 10; i++)
		l.insertEnd(i * 3 % 10 + 1);
	cout << l;
	mergeSort(l);
	cout << l;
}

template <typename T, typename R, typename I>
R foldr(I it, R (*op)(T, R), R const& nv) {
	if (!it)
		return nv;
	T x = *it++;
	return op(x, foldr(it, op, nv));
}

template <typename T, typename R, typename I>
R foldl(I it, R (*op)(R, T), R const& nv) {
	R result = nv;
	for(; it; ++it)
		result = op(result, *it);
	return result;
}

template <typename T, typename I>
void map(List<T, I>& l, T (*f)(T)) {
	for(I it = l.begin(); it; ++it)
		*it = f(*it);
}

int myplus(int x, int y) {
	return x + y;
}

int myproduct(int x, int y) {
	return x * y;
}

int mysquared(int x) {
	return x * x;
}

void testHigherOrder() {
	TestList l;
	for(int i = 1; i <= 10; i++)
		l.insertEnd(i);

	cout << l;

	cout << "Sum = " << foldr(l.begin(), myplus, 0) << endl;
	cout << "Product = " << foldl(l.begin(), myproduct, 1) << endl;
	map(l, mysquared);
	cout << l;
}


int main() {
	// testLinkedList();
	// testConcatenate();
	// testReverse();
	// testMergeSort();
	testHigherOrder();
	return 0;
}


