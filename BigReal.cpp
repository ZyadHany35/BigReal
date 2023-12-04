#include "BigReal.h"
#include <iostream>
#include <regex>
#include <string>
using namespace std;

BigReal BigReal::operator+ (const BigReal& other) {  
    string sumInt = "", sumFrac = "";
    BigReal first = *this;
    BigReal second = other;
    int carry = 0, comman, i;
    if (sign == other.sign) {
        string integer1 = first.integer, fraction1 = first.fraction; // to not modify the original real 
        string integer2 = second.integer, fraction2 = second.fraction;
        if (fraction1.size() > fraction2.size())
            fraction2.resize(fraction1.size(), '0');
        else
            fraction1.resize(fraction2.size(), '0');

        for (i = fraction1.size() - 1; i >= 0; --i) {
            int temp = carry + (fraction1[i] - '0') + (fraction2[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            }
            else
                carry = 0;
            sumFrac = to_string(temp) + sumFrac;
        }
        if (integer1.size() > integer2.size()) {
            int len = integer1.size() - integer2.size();
            for (int i = 0; i < len; ++i) {
                integer2 = "0" + integer2;
            }
        }
        else {
            int len = integer2.size() - integer1.size();
            for (int i = 0; i < len; ++i) {
                integer1 = "0" + integer1;
            }
        }

        for (i = integer1.size() - 1; i >= 0; --i) {
            int temp = carry + (integer1[i] - '0') + (integer2[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            }
            else
                carry = 0;
            sumInt = to_string(temp) + sumInt;
        }
        if (carry == 1)
            sumInt = '1' + sumInt;
    }
    else {
        if (other.sign == '-') {
             second.sign = '+';
             return first - second ;
        }
        else {
            first.sign = '+';
            return second - first;
        }
    }
    sumInt.erase(0, sumInt.find_first_not_of('0'));

    if (sumInt.empty())
        sumInt = "0";
    if (sumFrac.empty())
        sumFrac = "0";
    return BigReal(sign, sumInt, sumFrac);
};
