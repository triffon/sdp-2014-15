/*
 * decimal_fraction.cpp
 *
 *  Created on: 14.10.2014 г.
 *      Author: trifon
 */

#include "decimal_fraction.h"

DecimalFraction::DecimalFraction(int _m, int _n) :
  m(_m), n(_n) {
	whole = m / n;
}

DecimalFraction& DecimalFraction::operator>>(int& digit) {
	m %= n;
	m *= 10;
	digit = m / n;
	return *this;
}

DecimalFraction::operator bool() const {
	return m != 0;
}
