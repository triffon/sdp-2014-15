/*
 * queue_test.cpp
 *
 *  Created on: 11.11.2014 г.
 *      Author: trifon
 */

#include <iostream>
#include <cmath>
#include "squeue.cpp"
#include "lqueue.cpp"
using namespace std;

typedef LQueue<int> TestQueue;

void simpleQueueTest() {
	TestQueue q;
	for(int i = 1; i <= 20; i++)
		q.push(i);
	while (!q.empty())
		cout << q.pop() << ' ';
	cout << endl;
}

void pushPopTest() {
	TestQueue q;
	for(int i = 1; i <= 1000; i++) {
		q.push(i);
		cout << q.pop() << endl;
	}
}

int min(int x, int y) {
	return (x < y) ? x : y;
}

template <typename T>
void popx(Queue<T>& q, T const& x) {
	if (q.head() == x)
		q.pop();
}

void hemming(int n) {
	LQueue<int> q2, q3, q5;
	q2.push(1);
	q3.push(1);
	q5.push(1);
	for(int i = 1; i <= n; i++) {
		// извадим най-малкото число x от q2, q3, q5
		int x = min(q2.head(), min(q3.head(), q5.head()));
		popx(q2, x);
		popx(q3, x);
		popx(q5, x);
		// да изведем x
		cout << x << ' ';
		// да сложим в q2, q3, q5 съответно x*2, x*3 и x*5
		q2.push(x*2);
		q3.push(x*3);
		q5.push(x*5);
	}
}

// по дадена опашка q
// считаме, че q не е празна
// ще се връща най-малкият елемент
// а в q ще останат всички останали елементи
// очакваме sentinel
template <typename T>
T minQueue(Queue<T>& q, T const& sentinel = T()) {
	q.push(sentinel);
	T x = q.pop(), y;
	// for(int i = 0; i < q.length(); i++)
	while (q.pop(y) && y != sentinel) {
		if (y < x) {
			q.push(x);
			x = y;
		} else
			q.push(y);
	}
	// q.empty() || y == sentinel
	// в q ще са всички елементи без y == sentinel
	// и без x, което е най-малкия елемент
	return x;
}

template <typename T>
void sortQueue(Queue<T>& q, Queue<T>& result) {
	while (!q.empty())
		result.push(minQueue(q));
}

template <typename T>
void printQueue(LQueue<T> q) {
	while (!q.empty())
		cout << q.pop() << ' ';
	cout << endl;
}

void testSort() {
	TestQueue q, r;
	for(int i = 0; i < 10; i++)
		q.push(3 * i % 10);
	printQueue(q);
	sortQueue(q, r);
	printQueue(r);
}

int main() {
	// simpleQueueTest();
	// pushPopTest();
	// hemming(100);
	testSort();
	return 0;
}


