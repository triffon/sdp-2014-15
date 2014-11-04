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

class RadoInterpreter {
private:
	ifstream input;
	char memory[MEMORY_SIZE][MAX_SIZE];

	bool parseStatement();
	bool parseCommand();
	bool parseVariable();
	bool parseTerm();
	bool parseWord(char*);
	bool parseLiteral();
	bool parseExpression();
	bool parseExpressionTail();
	bool matchTerminal(char);
public:
	// конструиране с име на файл
	RadoInterpreter(char const*);
	bool execute();
};



#endif /* RADOINTERPRETER_H_ */
