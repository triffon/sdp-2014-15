/*
 * student.cpp
 *
 *  Created on: 28.03.2014
 *      Author: trifon
 */

#include <cstring>
#include <iostream>
using namespace std;

#include "student.h"

Student::Student(int _fn, char const* _name, double _grade)
				  : fn(_fn), grade(_grade) {
	strcpy(name, _name);
}

void Student::print() const {
	cout << fn << ' ' << name << ' ' << grade << endl;
}

void Student::setName(char const* _name) {
	strcpy(name, _name);
}

istream& operator>>(istream& is, Student& s) {
	is >> s.fn >> s.grade;
	is.getline(s.name, 100);
	return is;
}

ostream& operator<<(ostream& os, Student const& s) {
	return os << s.fn << ' ' << s.grade << ' ' << s.name << endl;
}
