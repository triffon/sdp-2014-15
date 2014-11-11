/*
 * queue_test.cpp
 *
 *  Created on: 11.11.2014 г.
 *      Author: trifon
 */

#include <iostream>
#include "squeue.cpp"
using namespace std;

void simpleQueueTest() {
	SQueue<int> q;
	for(int i = 1; i <= 20; i++)
		q.push(i);
	while (!q.empty())
		cout << q.pop() << ' ';
	cout << endl;
}

void pushPopTest() {
	SQueue<int> q;
	for(int i = 1; i <= 1000; i++) {
		q.push(i);
		cout << q.pop() << endl;
	}
}

int main() {
	simpleQueueTest();
	pushPopTest();
	return 0;
}


