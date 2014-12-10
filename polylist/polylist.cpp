/*
 * polylist.cpp
 *
 *  Created on: 9.12.2014 г.
 *      Author: trifon
 */

#include "pushpoplist.cpp"
#include "linked_list.cpp"

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
}

int main() {
	testPushPopList();
	return 0;
}
