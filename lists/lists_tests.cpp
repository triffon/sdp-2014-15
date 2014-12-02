/*
 * lists_tests.cpp
 *
 *  Created on: 2.12.2014 г.
 *      Author: trifon
 */

#include "linked_list.cpp"

typedef LinkedList<int> TestList;

void testLinkedList() {
	TestList l;
	for(int i = 1; i <= 5; i++) {
		l.insertEnd(i);
		l.insertBegin(i);
	}
	cout << l;
	for(LinkedListIterator<int> it = l.begin(); it; ++it) {
		if (*it % 2 == 0) {
			l.insertAfter(*it * 5 + 1, it);
			l.insertBefore(*it * 10, it);
		}
	}
	cout << l;
	for(LinkedListIterator<int> it = l.begin(); it; ++it) {
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

int main() {
	testLinkedList();
	return 0;
}


