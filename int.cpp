//Author: Benjamin Kleinberg

#include "int.h"

#include<iostream>
#include<fstream>
using std::ostream;
using std::istream;
using std::ifstream;

const Int Int::INF(1, 1);
const Int Int::N_INF(-1, 2);
const Int Int::NAN(0, 3);
int Int::displayASCII = 0;

/**
 * Private constructor for setting up constants
 * @param val the integer value to be set
 * @param flags the flags to mark the constant
 */
Int::Int(int val, int flags) {
	_val = val;
	_flags = flags;
}

/**
 * Public constructor to set up a standard integer
 * @param nVal the integer value to be set
 */
Int::Int(int nVal) {
	_val = nVal;
	_flags = 0;
}

/**
 * Less than operator
 */
int operator<(const Int &left, const Int &right) {
	int retVal = 0;

	if(left._flags == 0 && right._flags == 0)
		//Standard integer comparison
		retVal = left._val < right._val;
	else if(left == Int::INF)
		//If left is infinity, it is never smaller
		retVal = 0;
	else if(left == Int::N_INF)
		//If left is negative infinity, it is always smaller unless right is also negative infinity
		retVal = (right != Int::N_INF);
	else if(right == Int::INF)
		//If right is infinity, left is always smaller unless it is also infinity
		retVal = (left != Int::INF);
	else if(right == Int::N_INF)
		//If right is negative infinity, left is never smaller
		retVal = 0;

	return retVal;
}

int operator<(const Int &left, const int &right) {
	return left < Int(right);
}

int operator<(const int &left, const Int &right) {
	return Int(left) < right;
}

/**
 * Less than or equal operator
 */
int operator<=(const Int &left, const Int &right) {
	int retVal = 0;

	if(left._flags == 0 && right._flags == 0)
		//Standard integer comparison
		retVal = left._val <= right._val;
	else if(left == Int::INF)
		//If left is infinity, it is only smaller or equal when right is also infinity
		retVal = (right == Int::INF);
	else if(left == Int::N_INF)
		//If left is negative infinity, it is always smaller or equal
		retVal = 1;
	else if(right == Int::INF)
		//If right is infinity, left is always smaller or equal
		retVal = 1;
	else if(right == Int::N_INF)
		//If right is negative infinity, left is only smaller or equal when it is also negative infinty
		retVal = (left == Int::N_INF);

	return retVal;
}

int operator<=(const Int &left, const int &right) {
	return left <= Int(right);
}

int operator<=(const int &left, const Int &right) {
	return Int(left) <= right;
}

/**
 * Greater than operator
 */
int operator>(const Int &left, const Int &right) {
	int retVal = 0;

	if(left._flags == 0 && right._flags == 0)
		//Standard integer comparison
		retVal = left._val > right._val;
	else if(left == Int::INF)
		//If left is infinity, it is always larger unless right is also infinity
		retVal = (right != Int::INF);
	else if(left == Int::N_INF)
		//If left is negative infinity, it is never larger
		retVal = 0;
	else if(right == Int::INF)
		//If right is infinity, left is never larger
		retVal = 0;
	else if(right == Int::N_INF)
		//If right is negative infinity, left is larger unless right is also negative infinity
		retVal = (left != Int::N_INF);

	return retVal;
}

int operator>(const Int &left, const int &right) {
	return left > Int(right);
}

int operator>(const int &left, const Int &right) {
	return Int(left) > right;
}

/**
 * Greater than or equal operator
 */
int operator>=(const Int &left, const Int &right) {
	int retVal = 0;

	if(left._flags == 0 && right._flags == 0)
		//Standard integer comparison
		retVal = left._val >= right._val;
	else if(left == Int::INF)
		//If left is infinity, it is always larger or equal
		retVal = 1;
	else if(left == Int::N_INF)
		//If left is negative infinity, it is only larger or equal when right is also negative infinity
		retVal = (right == Int::N_INF);
	else if(right == Int::INF)
		//If right is infinity, left is only larger or equal when it is also infinity
		retVal = (left == Int::INF);
	else if(right == Int::N_INF)
		//If right is negative infinity, left is always larger or equal
		retVal = 1;

	return retVal;
}

int operator>=(const Int &left, const int &right) {
	return left >= Int(right);
}

int operator>=(const int &left, const Int &right) {
	return Int(left) >= right;
}

/**
 * Equality operator
 * Two integers are equal if they both are the same infinities or are the same regular integers.
 */
int operator==(const Int &left, const Int &right) {
	int retVal = 1;

	retVal = (left._flags == right._flags);
	if(retVal && left._flags == 0)
		retVal = (left._val == right._val);

	return retVal;
}

int operator==(const Int &left, const int &right) {
	return left == Int(right);
}

int operator==(const int &left, const Int &right) {
	return Int(left) == right;
}

/**
 * Inequality operator
 */
int operator!=(const Int &left, const Int &right) {
	return !(left == right);
}

int operator!=(const Int &left, const int &right) {
	return left != Int(right);
}

int operator!=(const int &left, const Int &right) {
	return Int(left) != right;
}

/**
 * Addition operator
 * Flags get combined bitwise.
 * Infinity + negative infinity = invalid integer.
 */
Int operator+(const Int &left, const Int &right) {
	Int retVal;

	retVal._val = left._val + right._val;
	retVal._flags = left._flags | right._flags;

	return retVal;
}

Int operator+(const Int &left, const int &right) {
	return left + Int(right);
}

Int operator+(const int &left, const Int &right) {
	return Int(left) + right;
}

/**
 * Addition and set operator
 * Flags get combined bitwise.
 * Infinity + negative infinity = invalid integer.
 */
void operator+=(Int &left, const Int &right) {
	left._val = left._val + right._val;
	left._flags = left._flags | right._flags;
}

void operator+=(Int &left, const int &right) {
	left += Int(right);
}

/**
 * Subtraction operator
 * Flags get reversed and combined bitwise
 * Infinity - infinity = invalid integer.
 */
Int operator-(const Int &left, const Int &right) {
	Int retVal;

	retVal._val = left._val - right._val;
	retVal._flags = left._flags;

	if(right._flags & 1)
		retVal._flags = retVal._flags | 2;
	if(right._flags & 2)
		retVal._flags = retVal._flags | 1;

	return retVal;
}

Int operator-(const Int &left, const int &right) {
	return left - Int(right);
}

Int operator-(const int &left, const Int &right) {
	return Int(left) - right;
}

/**
 * Subtraction and set operator
 * Flags get reversed and combined bitwise.
 * Infinity - infinity = invalid integer.
 */
void operator-=(Int &left, const Int &right) {
	left._val = left._val - right._val;

	if(right._flags & 1)
		left._flags = left._flags | 2;
	if(right._flags & 2)
		left._flags = left._flags | 1;
}

void operator-=(Int &left, const int &right) {
	left -= Int(right);
}

/**
 * Multiplication operator
 * Total negatives get added up to determine resulting flag.
 */
Int operator*(const Int &left, const Int &right) {
	Int retVal;

	if(left._flags || right._flags) {
		if(left == Int::NAN || right == Int::NAN)
			//Preserve invalid integers
			retVal = Int::NAN;

		else {
			int totalNegatives = 0;
			totalNegatives += (left._val < 0 || left._flags == 2);
			totalNegatives += (right._val < 0 || right._flags == 2);

			retVal._flags = totalNegatives % 2 + 1;
		}
	}
	else
		retVal._val = left._val * right._val;

	return retVal;
}

Int operator*(const Int &left, const int &right) {
	return left * Int(right);
}

Int operator*(const int &left, const Int &right) {
	return Int(left) * right;
}

/**
 * Division operator
 * Divisor cannot be an infinity.
 * Total negatives get added up to determine resulting flag.
 */
Int operator/(const Int &left, const Int &right) {
	Int retVal;

	if(left._flags || right._flags) {
		if(left == Int::NAN || right._flags)
			//Preserve invalid integers
			//Divisor being either infinity is invalid
			retVal = Int::NAN;

		else {
			int totalNegatives = 0;
			totalNegatives += (left._val < 0 || left._flags == 2);
			totalNegatives += (right._val < 0 || right._flags == 2);

			retVal._flags = totalNegatives % 2 + 1;
		}
	}
	else
		retVal._val = left._val / right._val;

	return retVal;
}

Int operator/(const Int &left, const int &right) {
	return left / Int(right);
}

Int operator/(const int &left, const Int &right) {
	return Int(left) / right;
}

/**
 * Modulus operator
 * Divisor cannot be an infinity.
 */
Int operator%(const Int &left, const Int &right) {
	Int retVal;

	if(left._flags || right._flags) {
		if(left == Int::NAN || right._flags)
			//Preserve invalid integers
			//Divisor being either infinity is invalid
			retVal = Int::NAN;

		else
			//Divident being negative results in a negative infinity
			retVal._flags = (left._val < 0 || left._flags == 2) + 1;
	}
	else
		retVal._val = left._val % right._val;

	return retVal;
}

Int operator%(const Int &left, const int &right) {
	return left % Int(right);
}

Int operator%(const int &left, const Int &right) {
	return Int(left) % right;
}


/**
 * Insertion operator
 */
ostream& operator<<(ostream& out, const Int& right) {

	switch(right._flags) {
	case 0: //Standard int
		out<< right._val;
		break;

	case 1: //Infinity
		if(Int::displayASCII)
			out<< Int::INF_CHAR;
		else
			out<< "inf";
		break;

	case 2: //Negative Infinity
		if(Int::displayASCII)
			out<< '-' << Int::INF_CHAR;
		else
			out<< "-inf";
		break;

	default: //Invalid flag
		out<< "-nan";
		break;
	}

	return out;
}

/**
 * Extraction operator
 */
istream& operator>>(istream& in, Int& right) {
	in>> right._val;
	right._flags = 0;

	return in;
}
