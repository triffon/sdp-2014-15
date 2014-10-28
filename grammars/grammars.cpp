/*
 * grammars.cpp
 *
 *  Created on: 28.10.2014 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;

bool matchTerminal(char const*& word, char t) {
	if (*word == t) {
		word++;
		return true;
	}
	return false;
}

bool parseS(char const*&);
bool parseT(char const*&);
bool parseU(char const*&);

int count = 0;

bool parseU(char const*& word) {
	if (*word == '{') {
		return matchTerminal(word, '{') &&
			   parseS(word) &&
			   matchTerminal(word, '}');
	}
	else
		return matchTerminal(word, 'a');
}


bool parseT(char const*& word) {
	if (*word == '[') {
		count++;
		return matchTerminal(word, '[') &&
			   parseU(word) &&
			   matchTerminal(word, ']');
	}
	else
		return matchTerminal(word, 'a');
}

bool parseS(char const*& word) {
	if (*word == '(') {
		return matchTerminal(word, '(') &&
			   parseT(word) &&
			   matchTerminal(word, ')');
	}
	else
		return matchTerminal(word, 'a');
}

bool parseE(char const*& word) {
	if (*word >= '0' && *word <= '9') {
		//return matchTerminal(word, *word);
		word++;
		return true;
	} else {
		return (matchTerminal(word, '+') ||
			    matchTerminal(word, '-') ||
			    matchTerminal(word, '*') ||
			    matchTerminal(word, '/')) &&
				parseE(word) && parseE(word);
	}
}

bool calculateE(char const*& word, double& result) {
	if (*word >= '0' && *word <= '9') {
		result = *word - '0';
		word++;
		return true;
	} else {
		char op = *word;
		double l, r;
		bool success =
			(matchTerminal(word, '+') ||
			matchTerminal(word, '-') ||
			matchTerminal(word, '*') ||
			matchTerminal(word, '/')) &&
			calculateE(word, l) &&
			calculateE(word, r);
		if (success) {
			switch(op) {
			case '+':result = l + r; break;
			case '-':result = l - r; break;
			case '*':result = l * r; break;
			case '/':result = l / r; break;
			}
		}
		return success;
	}
}

int main() {
	char word[100];
	cin.getline(word, 100);
	char const* p = word;
	bool recognizeS = parseS(p) && *p == '\0';
	cout << recognizeS << endl;
	cout << "Брой на квадратните скоби: " << count << endl;

	p = word;
	bool recognizeE = parseE(p) && *p == '\0';
	cout << recognizeE << endl;

	p = word;
	double result;
	recognizeE = calculateE(p, result) && *p == '\0';
	if (recognizeE) {
		cout << result << endl;
	} else
		cout << "ERROR!" << endl;
	return 0;
}
