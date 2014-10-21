/*
 * student.h
 *
 *  Created on: 28.03.2014
 *      Author: trifon
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
using namespace std;

class Student {
	int fn;
	char name[100];
	double grade;
public:

	// конструктори
	Student(int = 0, char const* = "", double = 0);

	// селектори
	int getFN() const { return fn; }
	char const* getName() const { return name; }
	double getGrade() const { return grade; }
	void print() const;

	// мутатори
	void setFN(int _fn) { fn = _fn; }
	void setGrade(double _grade) { grade = _grade; }
	void setName(char const*);

	friend istream& operator>>(istream&, Student&);
	friend ostream& operator<<(ostream&, Student const&);
};



#endif /* STUDENT_H_ */
