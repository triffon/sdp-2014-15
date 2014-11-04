/*
 * grammars.cpp
 *
 *  Created on: 28.10.2014 г.
 *      Author: trifon
 */

#include <iostream>
using namespace std;

#include "stack_automaton.h"

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

void testStackAutomaton() {
	StackAutomaton s;
	s.addDelta('a', '#', "a");
	s.addDelta('b', 'a', "b");
	s.addDelta('c', 'b', "");
	cout << s.recognize("abc") << endl;
	cout << s.recognize("ab") << endl;
	cout << s.recognize("abcd") << endl;
}

void testGrammars() {
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
}

struct Rule {
	char LHS;
	char const* RHS;
};

StackAutomaton buildAutomaton(Rule grammar[], int n) {
	StackAutomaton sa(grammar[0].LHS);
	// (1)
	for(int i = 0; i < n; i++)
		sa.addDelta(EPS, grammar[i].LHS, grammar[i].RHS);

	// (2)
	for(unsigned char c = 1; c < TABLE_SIZE; c++)
		sa.addDelta(c, c, "");

	return sa;
}

void testParentheses() {
	Rule grammar[] = {
						{ 'S', "(T)" },
						{ 'T', "[U]" },
						{ 'U', "{S}" },
						{ 'S', "a" },
						{ 'T', "a" },
						{ 'U', "a" }
	};
	StackAutomaton sa = buildAutomaton(grammar, 6);
	cout << sa.recognize("a") << endl;
	sa.reset();
	cout << sa.recognize("(a)") << endl;
	sa.reset();
	cout << sa.recognize("([{(a)}])") << endl;
	sa.reset();
	cout << sa.recognize("([a)]") << endl;
}

void testPN() {
	Rule grammar[] = {
							{ 'E', "+EE" },
							{ 'E', "-EE" },
							{ 'E', "*EE" },
							{ 'E', "/EE" },
							{ 'E', "0" },
							{ 'E', "1" },
							{ 'E', "2" },
							{ 'E', "3" },
							{ 'E', "4" },
							{ 'E', "5" },
							{ 'E', "6" },
							{ 'E', "7" },
							{ 'E', "8" },
							{ 'E', "9" }
		};
	StackAutomaton sa = buildAutomaton(grammar, 14);
	cout << sa.recognize("*+12-3/45") << endl;
}

void testArithmetic() {
	Rule grammar[] = {
			{ 'S', "S+T" },
			{ 'S', "S-T" },
			{ 'S', "T" },
			{ 'T', "T*F" },
			{ 'T', "T/F" },
			{ 'T', "F" },
			{ 'F', "(S)" },
			{ 'F', "0" },
			{ 'F', "1" },
			{ 'F', "2" },
			{ 'F', "3" },
			{ 'F', "4" },
			{ 'F', "5" },
			{ 'F', "6" },
			{ 'F', "7" },
			{ 'F', "8" },
			{ 'F', "9" }
	};
	StackAutomaton sa = buildAutomaton(grammar, 17);
	cout << sa.recognize("(1+2)*(3-4/5)") << endl;
}

void testArithmeticLL1() {
	Rule grammar[] = {
			{ 'S', "TA" },
			{ 'A', "+S" },
			{ 'A', "-S" },
			{ 'A', "" },
			{ 'T', "FB" },
			{ 'B', "*T" },
			{ 'B', "/T" },
			{ 'B', "" },
			{ 'F', "(S)" },
			{ 'F', "0" },
			{ 'F', "1" },
			{ 'F', "2" },
			{ 'F', "3" },
			{ 'F', "4" },
			{ 'F', "5" },
			{ 'F', "6" },
			{ 'F', "7" },
			{ 'F', "8" },
			{ 'F', "9" }
		};
	StackAutomaton sa = buildAutomaton(grammar, 19);
	cout << sa.recognize("1") << endl;
	sa.reset();
	cout << sa.recognize("(1+2)*(3-4/5)") << endl;
}

int main() {
	// testGrammars();
	// testStackAutomaton();
	// testParentheses();
	// testPN();
	// testArithmetic();
	testArithmeticLL1();
	return 0;
}
