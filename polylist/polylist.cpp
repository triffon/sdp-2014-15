/*
 * polylist.cpp
 *
 *  Created on: 9.12.2014 г.
 *      Author: trifon
 */

#include "pushpoplist.cpp"
#include "linked_list.cpp"
#include "slist.cpp"

typedef LinkedList<PushPop<int>*> PushPopList;

void testPushPopList() {
	PushPopQueue<int> q1, q2;
	PushPopStack<int> s1, s2;
	for(int i = 1; i <= 10; i++) {
		q1.push(i);
		s1.push(i);
		q2.push(i + 10);
		s2.push(i + 10);
	}
	PushPopList ppl;
	ppl.insertEnd(&q1);
	ppl.insertEnd(&s2);
	ppl.insertEnd(&s1);
	ppl.insertEnd(&q2);
	for(int i = 1; i <= 10; i++) {
		for(LinkedListIterator<PushPop<int>*> it = ppl.begin();
				it; ++it) {
			int x;
			(*it)->pop(x);
			cout << x << ' ';
		}
		cout << endl;
	}
	TestQueue<int> tq;
	tq.push(2);
}

void testSList() {
	SList l;
	l.insertEnd(new SInt(1));
	SList l2;
	l2.insertEnd(new SInt(2));
	l.insertEnd(&l2);
	SList l3;
	SList l5;
	l5.insertEnd(new SInt(3));
	SList l6;
	l6.insertEnd(new SInt(4));
	l5.insertEnd(&l6);
	l3.insertEnd(&l5);
	l3.insertEnd(new SInt(5));
	l.insertEnd(&l3);
	SList l4;
	l.insertEnd(&l4);
	l.print();
	cout << endl;

	LinkedList<int> ints;
	l.collectInts(ints);
	cout << ints;
}

int main() {
	// testPushPopList();
	testSList();
	return 0;
}
