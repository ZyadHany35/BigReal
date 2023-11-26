#pragma once
#include <iostream>
#include <string>
using namespace std;

class BigReal {
private:
	char sign = '+';
	string integer, fraction;
	bool isValidReal(const string& real); // True if correct real
public:
	BigReal() :integer("0"), fraction("0") {} 
	BigReal(char s, string intg, string frac) :sign(s), integer(intg), fraction(frac) {} 
	BigReal(string real); // Initialize from string
	//BigReal(const BigReal& other); // Copy constructor
	//BigReal& operator= (BigReal& other); // Assignment operator
	// Depending on how you store data, default can be enough
	void setNum(string real);
	BigReal operator+ (const BigReal& other);
	BigReal operator- (const BigReal& other);
	bool operator< (const BigReal& anotherReal);
	bool operator> (const BigReal& anotherReal);
	bool operator== (const BigReal& anotherReal);
	friend ostream& operator << (ostream& out, const BigReal& num);

};