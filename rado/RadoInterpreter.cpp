/*
 * RadoInterpreter.cpp
 *
 *  Created on: 4.11.2014 г.
 *      Author: trifon
 */

#include <cstring>
#include <iostream>
#include "RadoInterpreter.h"
using namespace std;

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

bool RadoInterpreter::parseCommand(Command& command) {
	char commandName[MAX_SIZE];
	bool success = parseWord(commandName);
	if (success) {
		if (strcmp(commandName, PRINT_COMMAND_NAME) == 0) {
			command = PRINT_COMMAND;
		} else
		/*
		if (strcmp(commandName, XXX_COMMAND_NAME) == 0) {
			command = XXX_COMMAND;
		} else
		*/
			return false;
	}
	return success;
}

bool RadoInterpreter::parseVariable(char& var) {
	// V -> a | ... | z
	return input.get(var) &&
			var >='a' && var <= 'z';
}

bool RadoInterpreter::parseLiteral(char* literal) {
	return matchTerminal('"') &&
			parseWord(literal) &&
			matchTerminal('"');
}

bool RadoInterpreter::parseTerm(char* term) {
	// T -> L | V
	char c = input.peek();
	bool success = false;
	if (c == '"') {
		// L
		success = parseLiteral(term);
	}
	else {
		// V
		char var;
		success = parseVariable(var);
		if (success) {
			strncpy(term, memory[varToIndex(var)], MAX_SIZE);
			term[MAX_SIZE-1] = '\0';
		}
	}
	return success;
}

bool RadoInterpreter::parseExpressionTail(char* value) {
	// F -> +E | e
	char c = input.peek();
	bool success = false;
	if (c == '+') {
		char tailvalue[MAX_SIZE];
		success = matchTerminal('+') &&
					  parseExpression(tailvalue);
		int value_len = strlen(value) + 1;
		if (value_len < MAX_SIZE)
			strncat(value, tailvalue, MAX_SIZE - value_len);
		return success;
	}
	else
		return true;

}

bool RadoInterpreter::parseExpression(char* value) {
	// E -> TF
	bool success = parseTerm(value) &&
			   parseExpressionTail(value);
	return success;
}

bool RadoInterpreter::parseStatement() {
	// S -> V = E | #C(E)
	char c = input.peek();
	char value[MAX_SIZE];
	if (!input)
		return false;
	if (c == '#') {
		// #C(E)
		Command command;
		bool success =
				matchTerminal('#') &&
				parseCommand(command) &&
				matchTerminal('(') &&
				parseExpression(value) &&
				matchTerminal(')');
		if (command == PRINT_COMMAND)
			cout << value << endl;
		return success;
	} else {
		// V = E
		char var;
		bool success =
				parseVariable(var) &&
				matchTerminal('=') &&
				parseExpression(value);
		strncpy(memory[varToIndex(var)], value, MAX_SIZE);
		memory[varToIndex(var)][MAX_SIZE-1] = '\0';
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
