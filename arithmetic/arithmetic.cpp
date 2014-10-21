/*
 * arithmetic.cpp
 *
 *  Created on: 21.10.2014 г.
 *      Author: trifon
 */

#include <iostream>
#include "lstack.cpp"
using namespace std;

double calculate_rpn(char const* rpn) {
	LinkedStack<double> stack;
	while (*rpn) {
		if (*rpn >= '0' && *rpn <= '9')
			stack.push(*rpn-'0');
		else {
			double r = stack.pop();
			double l = stack.pop();
			switch (*rpn) {
			case '+':stack.push(l + r);break;
			case '-':stack.push(l - r);break;
			case '*':stack.push(l * r);break;
			case '/':stack.push(l / r);break;
			}
		}
		rpn++;
	}
	return stack.pop();
}

int main() {
	char expr[100];
	cin.getline(expr, 100);
	cout << calculate_rpn(expr) << endl;
	return 0;
}


