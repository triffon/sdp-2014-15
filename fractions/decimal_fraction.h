/*
 * decimal_fraction.h
 *
 *  Created on: 14.10.2014 г.
 *      Author: trifon
 */

#ifndef DECIMAL_FRACTION_H_
#define DECIMAL_FRACTION_H_

class DecimalFraction {
private:
	int m, n, whole;
public:
	DecimalFraction(int, int);
	int getWhole() const { return whole; }
	DecimalFraction& operator>>(int&);
	operator bool() const;
};



#endif /* DECIMAL_FRACTION_H_ */
