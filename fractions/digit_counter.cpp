/*
 * digit_counter.cpp
 *
 *  Created on: 14.10.2014 г.
 *      Author: trifon
 */

#include "digit_counter.h"

DigitCounter::DigitCounter(int d) :
  digit(d), dcounter(0), counter(0) {
}

DigitCounter& DigitCounter::operator<<(int d) {
	counter++;
	if (d == digit) dcounter++;
	return *this;
}


