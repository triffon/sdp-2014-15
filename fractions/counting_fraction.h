/*
 * counting_fraction.h
 *
 *  Created on: 14.10.2014 г.
 *      Author: trifon
 */

#ifndef COUNTING_FRACTION_H_
#define COUNTING_FRACTION_H_

class CountingFraction {
	int count;
	int buffer, bufferLength;
	void refillBuffer(int);
public:
	CountingFraction(int);
	CountingFraction& operator>>(int&);
	operator bool const() { return true; }
};



#endif /* COUNTING_FRACTION_H_ */
