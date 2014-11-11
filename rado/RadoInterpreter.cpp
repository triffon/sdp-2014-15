/*
 * RadoInterpreter.cpp
 *
 *  Created on: 4.11.2014 г.
 *      Author: trifon
 */

#include <cstring>
#include "RadoInterpreter.h"

RadoInterpreter::RadoInterpreter(const char* filename) :
   input(filename) {
	for(int i = 0; i < MEMORY_SIZE; i++)
		memory[i][0] = '\0';
}

bool RadoInterpreter::matchTerminal(char c) {
	char t;
	return input.get(t) && c == t;
}

bool RadoInterpreter::parseWord(char* word) {
	// Разпознава дума от малки латински букви
	char c;
	int i = 0;
	while (input.get(c) && (c == ' ' || (c >= 'a' && c <= 'z')))
		word[i++] = c;
	if (!input)
		return false;
	// последният символ, който прочетем в c
	// няма да е малка латинска буква
	// трябва да го върнем обратно!
	input.putback(c);
	word[i] = '\0';
	return true;
}

bool RadoInterpreter::parseCommand() {
	char command[MAX_SIZE];
	return parseWord(command) && strcmp(command, "print") == 0;
}

bool RadoInterpreter::parseVariable() {
	// V -> a | ... | z
	char var;
	bool success = input.get(var) && var >='a' && var <= 'z';
	return success;
}

bool RadoInterpreter::parseLiteral() {
	char literal[MAX_SIZE];
	return matchTerminal('"') &&
			parseWord(literal) &&
			matchTerminal('"');
}

bool RadoInterpreter::parseTerm() {
	// T -> L | V
	char c = input.peek();
	bool success = false;
	if (c == '"')
		// L
		success = parseLiteral();
	else
		success = parseVariable();
	// TODO: действия по пресмятане на терма
	return success;
}

bool RadoInterpreter::parseExpressionTail() {
	// F -> +E | e
	char c = input.peek();
	bool success = false;
	if (c == '+') {
		success = matchTerminal('+') &&
					  parseExpression();
		// TODO: действия по пресмятане на ExpressionTail
		return success;
	}
	else
		return true;

}

bool RadoInterpreter::parseExpression() {
	// E -> TF
	bool success = parseTerm() && parseExpressionTail();
	// TODO: действия по пресмятане на израза
	return success;
}

bool RadoInterpreter::parseStatement() {
	// S -> V = E | #C(E)
	char c = input.peek();
	char buffer[MAX_SIZE];
	if (!input)
		return false;
	if (c == '#') {
		// #C(E)
		bool success =
				matchTerminal('#') &&
				parseCommand() &&
				matchTerminal('(') &&
				parseExpression() &&
				matchTerminal(')');
		// TODO: действия по изпълнение на командата
		return success;
	} else {
		// V = E
		bool success =
				parseVariable() &&
				matchTerminal('=') &&
				parseExpression();
		// TODO: действия по присвояване на променливата
		return success;
	}

}

bool RadoInterpreter::execute() {

	if (!input)
		return false;

	// P -> SP | e
	while (input.peek() != EOF) {
		if (!(parseStatement() &&
			  matchTerminal('\n')))
			return false;
	}
	return true;
}
