/*
 * dictionary.h
 *
 *  Created on: 20.01.2015 г.
 *      Author: trifon
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "linked_list.cpp"

template <typename K, typename V>
class Dictionary {
public:
	virtual V* search(K const&) = 0;
	virtual bool add(K const&, V const&) = 0;
	virtual bool remove(K const&) = 0;
	virtual LinkedList<K> keys() const = 0;
	virtual LinkedList<V> values() const = 0;
	virtual ~Dictionary() {}
};



#endif /* DICTIONARY_H_ */
