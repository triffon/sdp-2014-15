/*
 * list_dictionary.cpp
 *
 *  Created on: 20.01.2015 г.
 *      Author: trifon
 */

#include "dictionary.h"

template <typename K, typename V>
class ListDictionary : public Dictionary<K, V> {
	LinkedList<K> keyList;
	LinkedList<V> valueList;

public:
	V* search(K const& k) {
		LinkedListIterator<K> kit = keyList.begin();
		LinkedListIterator<V> vit = valueList.begin();
		while (kit && *kit != k) {
			++kit;
			++vit;
		}
		// !kit <-> ключа го няма
		// *kit == k <-> връщаме *vit
		if (!kit)
			return NULL;
		return &*vit;
	}

	bool add(K const& k, V const& v) {
		if (search(k))
			return false;
		keyList.insertEnd(k);
		valueList.insertEnd(v);
		return true;
	}

	bool remove(K const& k) {
		LinkedListIterator<K> kit = keyList.begin();
		LinkedListIterator<V> vit = valueList.begin();
		while (kit && *kit != k) {
			++kit;
			++vit;
		}
		// !kit <-> ключа го няма
		// *kit == k <-> връщаме *vit
		if (!kit)
			return false;
		K ktmp;
		V vtmp;
		keyList.deleteAt(ktmp, kit);
		valueList.deleteAt(vtmp, vit);
		return true;
	}

	LinkedList<K> keys() const { return keyList; }
	LinkedList<V> values() const { return valueList; }
};


