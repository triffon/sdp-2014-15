/*
 * streams.cpp
 *
 *  Created on: 14.10.2014 г.
 *      Author: trifon
 */

#include <iostream>
#include <iomanip>
#include <strstream>
using namespace std;

void ostreams() {
	char d[] = { 65, 66, 67, 68, 69 };
	cout.put(65);
	cout << 65;
	cout.write(d, 5);
	int n = 10000;
	cout.write((const char*)&n, sizeof(n));
}

void istreams() {
	int d;
	cin >> d;
	cout << d << endl;
	int n;
	cin.read((char*)&n, sizeof(n));
	cout.write((const char*)&n, sizeof(n));
	cout << n;
}

void peektest() {
	char c;
	// cin >> c;
	// лошо!
	// istrstream cin("123");

	// лошо!
	// istrstream s("123");
	// istream& cin = s;

	c = cin.peek();
	if (c >= '0' && c <= '9') {
		int d;
		// cin.putback(c);
		cin >> d;
		cout << "Число: " << d << endl;
	} else {
		cout << "Символ: " << c << endl;
		cin.get();
	}
	cin >> c;
	cout << "Втори символ: " << c << endl;
}

void failtest() {
	int d1, d2;
	cin >> d1 >> d2;
	if (!cin) {
		cerr << "Грешка: " << cin.rdstate() << endl;
		cerr << "EOF: " << cin.eof() << endl;
		cerr << "FAIL: " << cin.fail() << endl;
		cerr << "BAD: " << cin.bad() << endl;
	} else
		cout << "Числа: " << d1 << ' ' << d2 << endl;
}

void recovertest() {
	int d = 0;
	do {
		cout << "d = ";
		cin >> d;
		if (!cin) {
			cout << "Не сте въвели число!\n";
			cin.clear();
			while (cin.peek() != '\n')
				cin.get();
		}
	} while (d == 0);
	cout << "Браво: " << d << endl;
}

ostream& bang(ostream& os) {
	return os << setw(15) << setfill('!');
}

void manipulatortest() {
	cout << setw(15) << setfill('!');
	cout << 0.00000001 << endl;
	cout << bang << 0.0001 << endl;

	cout << setiosflags(ios::scientific);
	cout << 0.00000001 << endl;
	cout << 0.0001 << endl;
	cout << resetiosflags(ios::scientific);


	cout << setiosflags(ios::fixed);
	cout << 0.00000001 << endl;
	cout << 0.0001 << endl;

}

int main() {
	// ostreams();
	// istreams();
	// peektest();
	// failtest();
	// recovertest();
	manipulatortest();
	return 0;
}
