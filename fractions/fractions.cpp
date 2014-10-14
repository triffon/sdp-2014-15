/*
 * fractions.cpp
 *
 *  Created on: 14.10.2014 г.
 *      Author: trifon
 */


#include <iostream>
#include "decimal_fraction.h"
#include "counting_fraction.h"
#include "digit_counter.h"
using namespace std;

void decimalFraction(int m, int n) {
	cout << m / n;
	m %= n;
	m *= 10;
	cout << '.';
	while (m != 0)
	{
		cout << m / n;
		m %= n;
		m *= 10;
	}
	cout << endl;
}

void countingFraction(int n) {
	cout << 0 << '.';
	while (n < 100)
		cout << n++;
}

int main() {
	int m, n; cin >> m >> n;
	// decimalFraction(m, n);
	// countingFraction(1);
	DecimalFraction df(m, n);
	CountingFraction cf(1);
	cout << df.getWhole() << '.';
	int digit;
	int count = 0;

	while (cf >> digit && count < 10000) {
		cout << digit;
		count++;
	}
	cout << endl;
	cerr << "Грешка!\n";

	DigitCounter dc(5);

	while (dc.getCount() < 50) {
		df >> digit;
		dc << digit;
	}


	cout << "Намерихме цифрата 5 за 50-ти път ";
	cout << "на позиция " << dc.getTotalCount();
	cout << endl;

	return 0;
}

