/*
 * dictionary_examples.cpp
 *
 *  Created on: 20.01.2015 г.
 *      Author: trifon
 */

#include "list_dictionary.cpp"
#include <iostream>
using namespace std;

typedef ListDictionary<int, int> TestDictionary;

void testDictionary() {
	TestDictionary dict;
	for(int i = 1; i <= 10; i++)
		dict.add(i, i * 2);
	cout << "5 -> " << *dict.search(5) << endl;
	dict.remove(5);
	if (!dict.search(5))
		cout << "Няма стойност за 5!" << endl;
}

int main() {
	testDictionary();
	return 0;
}


