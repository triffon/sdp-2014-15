/*
 * files.cpp
 *
 *  Created on: 21.10.2014 г.
 *      Author: trifon
 */

#include <fstream>
#include <iostream>
using namespace std;

void testofiles() {
	ofstream f1("test.txt");
	f1 << "This is my text file" << endl;
	f1 << 10 << ' ' << 5.6;
	f1.close();

	ofstream f2("test.bin", ios::out | ios::binary);
	for(int i = 0; i <= 20; i++)
		f2.put(i);
	double d[] = { 1.2, 3.4, 5.6, 7.8 };
	f2.write((char const*)d, sizeof(d));
	f2.close();
}

void testifiles() {
	ifstream f1("test.txt");
	char line[100];
	f1.getline(line, 100);
	int n;
	double d;
	f1 >> n >> d;
	cout << "line = " << line << endl;
	cout << "n = " << n << endl;
	cout << "d = " << d << endl;
	f1.close();

	ifstream f2("test.bin", ios::in | ios::binary);
	for(int i = 0; i <= 20; i++) {
		cout << f2.get() << endl;
	}
	double da[100];
	f2.read((char*)da, 4 * sizeof(double));
	for(int i = 0; i < 4; i++)
		cout << da[i] << endl;
	f2.seekg(-2 * sizeof(double), ios::cur);
	cout << f2.tellg() << endl;
	f2.read((char*)&d, sizeof(double));
	cout << "d = " << d << endl;
	f2.close();

	fstream f3("test.txt", ios::in | ios::out);
	char word[100];
	f3 >> word;
	f3 << "was";
	f3.close();
}

int main() {
	// testofiles();
	testifiles();
	return 0;
}


