/*
 * counting_fraction.cpp
 *
 *  Created on: 14.10.2014 г.
 *      Author: trifon
 */

#include "counting_fraction.h"

CountingFraction::CountingFraction(int _n) : count(_n) {
	refillBuffer(count);
}

void CountingFraction::refillBuffer(int n) {
	// буферът съдържа числото n наобратно
	buffer = 0;
	bufferLength = 0;
	while (n > 0) {
		buffer *= 10;
		buffer += n % 10;
		n /= 10;
		bufferLength++;
	}
}

CountingFraction& CountingFraction::operator>>(int& digit) {
	if (bufferLength == 0)
		// презареждаме буфера
		refillBuffer(++count);

	// извеждаме последната цифра
	digit = buffer % 10;

	// махаме последната цифра от буфера
	buffer /= 10;
	bufferLength--;

	return *this;
}


