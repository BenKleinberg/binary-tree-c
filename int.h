//Author: Benjamin Kleinberg

#ifndef INT_H_
#define INT_H_

#include<iostream>
#include<fstream>
#include<limits>
using std::ostream;
using std::istream;
using std::ifstream;
using std::numeric_limits;

class Int {
private:
	/**
	 * bit 0: infinity
	 * bit 1: negative infinity
	 */
	int _flags;
	int _val;

	Int(int val, int flags);

	//ASCII value for the infinity symbol
	static const char INF_CHAR = char(8734);

public:

	Int(int nVal = 0);

	static const Int INF;
	static const Int N_INF;
	static const Int NAN;

	static int displayASCII;

	friend int operator<(const Int &left, const Int &right);
	friend int operator<(const Int &left, const int &right);
	friend int operator<(const int &left, const Int &right);

	friend int operator<=(const Int &left, const Int &right);
	friend int operator<=(const Int &left, const int &right);
	friend int operator<=(const int &left, const Int &right);

	friend int operator>(const Int &left, const Int &right);
	friend int operator>(const Int &left, const int &right);
	friend int operator>(const int &left, const Int &right);

	friend int operator>=(const Int &left, const Int &right);
	friend int operator>=(const Int &left, const int &right);
	friend int operator>=(const int &left, const Int &right);

	friend int operator==(const Int &left, const Int &right);
	friend int operator==(const Int &left, const int &right);
	friend int operator==(const int &left, const Int &right);

	friend int operator!=(const Int &left, const Int &right);
	friend int operator!=(const Int &left, const int &right);
	friend int operator!=(const int &left, const Int &right);

	friend Int operator+(const Int &left, const Int &right);
	friend Int operator+(const Int &left, const int &right);
	friend Int operator+(const int &left, const Int &right);

	friend void operator+=(Int &left, const Int &right);
	friend void operator+=(Int &left, const int &right);

	friend Int operator-(const Int &left, const Int &right);
	friend Int operator-(const Int &left, const int &right);
	friend Int operator-(const int &left, const Int &right);

	friend void operator-=(Int &left, const Int &right);
	friend void operator-=(Int &left, const int &right);

	friend Int operator*(const Int &left, const Int &right);
	friend Int operator*(const Int &left, const int &right);
	friend Int operator*(const int &left, const Int &right);

	friend Int operator/(const Int &left, const Int &right);
	friend Int operator/(const Int &left, const int &right);
	friend Int operator/(const int &left, const Int &right);

	friend Int operator%(const Int &left, const Int &right);
	friend Int operator%(const Int &left, const int &right);
	friend Int operator%(const int &left, const Int &right);

	operator double() const{
		double retVal = 0;

		if(_flags == 1)
			retVal = numeric_limits<double>::infinity();
		else if(_flags == 2)
			retVal = -numeric_limits<double>::infinity();
		else
			retVal = (double)_val;

		return retVal;
	}

	friend ostream& operator<<(ostream& out, const Int &right);
	friend istream& operator>>(istream& in, Int &right);
};

#endif /* INT_H_ */
