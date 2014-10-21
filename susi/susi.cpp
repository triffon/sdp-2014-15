/*
 * susi.cpp
 *
 *  Created on: 21.10.2014 г.
 *      Author: trifon
 */

#include <fstream>
using namespace std;
#include "student.h"

void input_students() {
	Student s;
	ofstream sf("students.txt");
	do {
		cin >> s;
		cout << s;
		if (s.getFN() != 0)
			sf << s;
	} while (s.getFN() != 0);
}

void transfer_to_main_book() {
	ifstream sf("students.txt");
	ofstream bk("main.bk", ios::out | ios::binary);
	Student s;
	while (sf >> s) {
		if (s.getGrade() >= 3)
			bk.write((char const*)&s, sizeof(Student));
	}
}

void increase_grade(int fn) {
	fstream bk("main.bk", ios::in | ios::out | ios::binary);
	Student s;
	while (bk.read((char*)&s, sizeof(Student))
			&& s.getFN() != fn);
	if (!bk.eof()) {
		s.setGrade(s.getGrade() + 1);
		bk.seekg(-sizeof(Student), ios::cur);
		bk.write((char const*)&s, sizeof(Student));
	}
}

int main() {
	/*
	ofstream mb("main.bk");
	Student s(40000, "Ivan", 5.5);
	mb.write((const char*)&s, sizeof(Student));
	mb.close();
	*/
	//input_students();
	//transfer_to_main_book();
	increase_grade(40005);

	return 0;
}


