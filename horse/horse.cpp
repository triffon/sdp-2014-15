/*
 * horse.cpp
 *
 *  Created on: 18.11.2014 г.
 *      Author: trifon
 */

#include <iostream>
#include <cmath>
#include "lqueue.cpp"
#include "lstack.cpp"
using namespace std;

const int MAX = 8;
int board[MAX][MAX] = { 0 };

struct Position {
	Position(int _x = 0, int _y = 0, int _move = 0) :
		x(_x), y(_y), move(_move) {}
	bool operator==(Position const& p) const {
		return x == p.x && y == p.y;
	}
	bool operator!=(Position const& p) const {
		return !(*this == p);
	}
	int x, y, move;
};

ostream& operator<<(ostream& os, Position const& p) {
	return os << '(' << p.x << ',' << p.y <<
			',' << p.move << ')' << endl;
}

istream& operator>>(istream& is, Position& p) {
	return is >> p.x >> p.y;
}

bool valid(Position p) {
	return p.x >= 0 && p.y >= 0 &&
			p.x < MAX && p.y < MAX &&
			board[p.x][p.y] == 0;
}

void printBoard() {
	for(int i = 0; i < MAX; i++) {
		for(int j = 0; j < MAX; j++)
			cout << board[i][j] << ' ';
		cout << endl;
	}
}

template <typename T>
ostream& operator<<(ostream& os, LinkedStack<T> s) {
	while (!s.empty())
		os << s.pop() << endl;
	return os;
}

bool horseStep(Position a, Position b) {
	return abs(a.x - b.x) * abs(a.y - b.y) == 2;
}

// с колко стъпки можем да стигнем от start до end
int horse(Position start, Position end) {
	LQueue<Position> q;
	LinkedStack<Position> s;
	q.push(start);
	Position current;
	while (q.pop(current) && current != end) {
		// вземаме текущата позиция на коня
		// стъпваме на нея
		board[current.x][current.y] = current.move;
		s.push(current);
		// добавяме в опашката всички необходени
		// позиции, на които може да стъпи конят
		for(int x = current.x - 2; x <= current.x + 2; x++)
			if (x != current.x)
				for(int d = -1; d <= 1; d += 2) {
					int y = current.y + d * (3 - abs(x - current.x));
					Position p(x, y, current.move + 1);
					if (valid(p))
						q.push(p);
				}
	}
	// q.empty() <-> не можем да стигнем до end
	// current == end <-> намерили сме решение
	if (!q.empty()) {
		board[current.x][current.y] = current.move;
		cout << current << endl;
		while (!s.empty()) {
			if (horseStep(current, s.last())) {
				current = s.last();
				cout << current << endl;
			}
			s.pop();
		}
		return current.move;
	}
	// cout << s << endl;
	return -1;
}

int main() {
	Position start, end;
	cout << "start = "; cin >> start;
	cout << "end = "; cin >> end;
	start.move = 1;
	cout << horse(start, end) << endl;
	printBoard();
	return 0;
}


