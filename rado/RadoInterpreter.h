/*
 * RadoInterpreter.h
 *
 *  Created on: 4.11.2014 г.
 *      Author: trifon
 */

#ifndef RADOINTERPRETER_H_
#define RADOINTERPRETER_H_

int const MAX_SIZE = 1000;
int const MEMORY_SIZE = 26;

#include <fstream>
using namespace std;

typedef int Command;
const Command PRINT_COMMAND = 1;
const char PRINT_COMMAND_NAME[] = "print";

class RadoInterpreter {
private:
	ifstream input;
	char memory[MEMORY_SIZE][MAX_SIZE];

	bool parseStatement();
	bool parseCommand(Command&);
	bool parseVariable(char&);
	bool parseTerm(char*);
	bool parseWord(char*);
	bool parseLiteral(char*);
	bool parseExpression(char*);
	bool parseExpressionTail(char*);
	bool matchTerminal(char);

	int varToIndex(char var) { return var - 'a'; }
public:
	// конструиране с име на файл
	RadoInterpreter(char const*);
	bool execute();
};



#endif /* RADOINTERPRETER_H_ */
