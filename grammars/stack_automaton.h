/*
 * stack_automaton.h
 *
 *  Created on: 28.10.2014 г.
 *      Author: trifon
 */

#ifndef STACK_AUTOMATON_H_
#define STACK_AUTOMATON_H_

#include "lstack.cpp"
#include <string>
using namespace std;

const int TABLE_SIZE = 128;
typedef string Word;
const char EPS = '\0';
const char STACK_BOTTOM = '#';

class StackAutomaton {
private:
	LinkedStack<char> stack;
	LinkedStack<Word> delta[TABLE_SIZE][TABLE_SIZE];

	void pushToStack(char const*);
public:
	StackAutomaton();
	void addDelta(char, char, Word);
	bool recognize(char const*);
	bool recognizeWithChars(char const*, char, char);
};



#endif /* STACK_AUTOMATON_H_ */
