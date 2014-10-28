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

int priority(char op) {
	switch (op) {
	case '+':
	case '-':return 1;
	case '*':
	case '/':return 2;
	default:return -1;
	}
}

void expr_to_rpn(char const* expr, char* rpn) {
	LinkedStack<char> opstack;

	while(*expr) {
		if (*expr >= '0' && *expr <= '9')
			*rpn++ = *expr;
		else
		if (*expr == '(')
			opstack.push(*expr);
		else
		if (*expr == ')') {
			char op = opstack.pop();
			while (op != '(') {
				*rpn++ = op;
				op = opstack.pop();
			}
			/*
			while ((op = opstack.pop()) != '(')
				*rpn++ = op;
		    */
		} else {
			// *expr е операция
			// първо: вадим всички операции
			// с по-висок или равен приоритет
			while (!opstack.empty() &&
				   priority(opstack.last()) >=
				   priority(*expr))
				*rpn++ = opstack.pop();
			opstack.push(*expr);
		}
		expr++;
	}
	while (!opstack.empty())
		*rpn++ = opstack.pop();
	// терминираме низа
	*rpn = '\0';
}

void apply_operation(LinkedStack<double>& rstack,
					 char op) {
	double r = rstack.pop();
	double l = rstack.pop();
	switch (op) {
	case '+':rstack.push(l + r);break;
	case '-':rstack.push(l - r);break;
	case '*':rstack.push(l * r);break;
	case '/':rstack.push(l / r);break;
	}
}

double calculate_expr(char const* expr) {
	LinkedStack<char> opstack;
	LinkedStack<double> rstack;

	while(*expr) {
		if (*expr >= '0' && *expr <= '9')
			rstack.push(*expr-'0');
		else
		if (*expr == '(')
			opstack.push(*expr);
		else
		if (*expr == ')') {
			char op = opstack.pop();
			while (op != '(') {
				apply_operation(rstack, op);
				op = opstack.pop();
			}
			/*
			while ((op = opstack.pop()) != '(')
				*rpn++ = op;
		    */
		} else {
			// *expr е операция
			// първо: вадим всички операции
			// с по-висок или равен приоритет
			while (!opstack.empty() &&
				   priority(opstack.last()) >=
				   priority(*expr))
				apply_operation(rstack,opstack.pop());
			opstack.push(*expr);
		}
		expr++;
	}
	while (!opstack.empty())
		apply_operation(rstack, opstack.pop());

	return rstack.pop();
}

int main() {
	char expr[100];
	cin.getline(expr, 100);
	char rpn[100];
	expr_to_rpn(expr, rpn);
	cout << rpn << endl;
	cout << calculate_rpn(rpn) << endl;
	cout << calculate_expr(expr) << endl;
	return 0;
}


