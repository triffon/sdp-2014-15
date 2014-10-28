/*
 * stack_automaton.cpp
 *
 *  Created on: 28.10.2014 г.
 *      Author: trifon
 */

#include "stack_automaton.h"

StackAutomaton::StackAutomaton() {
	stack.push(STACK_BOTTOM);
}

void StackAutomaton::addDelta(char input_char, char stack_char,
		      Word w) {
	delta[input_char][stack_char].push(w);
}

void StackAutomaton::pushToStack(char const* sw) {
	char const *p = sw;
	while (*p) p++;
	// p сочи към края на низа
	do {
		p--;
		stack.push(*p);
	} while (p != sw);
}

bool StackAutomaton::recognizeWithChars(char const* w, char a, char g) {
	LinkedStack<Word> transitions = delta[a][g];
	while (!transitions.empty()) {
		LinkedStack<char> save_stack = stack;
		// пробваме текущия преход
		Word stack_word = transitions.pop();
		pushToStack(stack_word.c_str());
		if (recognize(w+1))
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
	if (*w == '\0')
		return stack.empty();

	// махаме първия символ от стека
	char g = stack.pop();

	// опитваме преход с първия символ на думата
	// опитваме епсилон преходите
	return recognizeWithChars(w, w[0], g) ||
		recognizeWithChars(w, EPS, g);
}
