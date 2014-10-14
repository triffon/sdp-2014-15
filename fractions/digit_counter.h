/*
 * digit_counter.h
 *
 *  Created on: 14.10.2014 г.
 *      Author: trifon
 */

#ifndef DIGIT_COUNTER_H_
#define DIGIT_COUNTER_H_

class DigitCounter {
	int digit;
	int dcounter;
	int counter;
public:
	DigitCounter(int);
	int getCount() const { return dcounter; }
	int getTotalCount() const { return counter; }
	DigitCounter& operator<<(int);
};



#endif /* DIGIT_COUNTER_H_ */
