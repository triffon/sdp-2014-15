/*
 * stack_automaton.cpp
 *
 *  Created on: 28.10.2014 г.
 *      Author: trifon
 */

#include "stack_automaton.h"

StackAutomaton::StackAutomaton(char _bottom) :
	bottom(_bottom) {
	reset();
}

void StackAutomaton::addDelta(char input_char, char stack_char,
		      Word w) {
	delta[input_char][stack_char].push(w);
}

void StackAutomaton::pushToStack(char const* sw) {
	char const *p = sw;
	while (*p)
		p++;
	// p сочи към края на низа
	while (p != sw)
		stack.push(*--p);
}

bool StackAutomaton::recognizeWithChars(char const* w, char a, char g) {
	LinkedStack<Word> transitions = delta[a][g];
	while (!transitions.empty()) {
		LinkedStack<char> save_stack = stack;
		// пробваме текущия преход
		Word stack_word = transitions.pop();
		pushToStack(stack_word.c_str());
		if (recognize(w))
			// преходът е бил успешен!!!
			// думата е разпозната
			return true;
		// преходът не е бил успешен
		// възстановяваме старото състояние на стека
		stack = save_stack;
	}
	return false;
}

bool StackAutomaton::recognize(char const* w) {
	if (stack.empty())
		return *w == '\0';

	// !stack.empty(), но може *w == '\0'

	// махаме първия символ от стека
	char g = stack.pop();

	// опитваме преход с първия символ на думата
	// опитваме епсилон преходите
	if (*w != '\0' && recognizeWithChars(w + 1, w[0], g))
		return true;
	return recognizeWithChars(w, EPS, g);
}

void StackAutomaton::reset() {
	while (!stack.empty())
		stack.pop();
	stack.push(bottom);
}
