/*
 * main.cpp
 *
 *  Created on: 4.11.2014 г.
 *      Author: trifon
 */

#include "RadoInterpreter.h"
#include <iostream>
using namespace std;

int main() {
	RadoInterpreter ri("hello.rado");
	bool success = ri.execute();
	cout << "Success: " << success << endl;
}


