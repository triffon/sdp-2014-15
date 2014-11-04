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
	return input >> t && c == t;
}

bool RadoInterpreter::parseWord(char* word) {
	// Разпознава дума от малки латински букви
	char c;
	int i = 0;
	while (input >> c && (c >= 'a' && c <= 'z' || c == ' '))
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
	bool success = input >> var && var >='a' && var <= 'z';
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
	char c;
	char buffer[MAX_SIZE];
	if (!(input >> c))
		return false;
	if (c == '#') {
		// #C(E)
		bool success =
				parseCommand() &&
				matchTerminal('(') &&
				parseExpression() &&
				matchTerminal(')');
		// TODO: действия по изпълнение на командата
		input.getline(buffer, MAX_SIZE);
		return success;
	} else {
		// V = E
		bool success =
				parseVariable() &&
				matchTerminal('=') &&
				parseExpression();
		// TODO: действия по присвояване на променливата
		input.getline(buffer, MAX_SIZE);
		return success;
	}

}

bool RadoInterpreter::execute() {

	if (!input)
		return false;

	// P -> SP | e
	while (input) {
		if (!parseStatement())
			return false;
	}
	return true;
}
