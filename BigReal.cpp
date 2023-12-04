#include "BigReal.h"
#include <iostream>
#include <regex>
#include <string>
using namespace std;

bool BigReal:: isValidReal(const string& real){
        if (regex_match(real, regex("[+-]?\\d*\\.?\\d*")))
            return true;

        else  return false;
}

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
BigReal BigReal::operator- (const BigReal& other) {
    string subInt = "", subFrac = "";
    BigReal first = *this;
    BigReal second = other;

    int borrow = 0, i;

    if (sign == other.sign) {
        string integer1 = first.integer, fraction1 = first.fraction; // to not modify the original real 
        string integer2 = second.integer, fraction2 = second.fraction;
        if (sign == '-') {
            first.sign = second.sign = '+' ;
            return second - first;
        }
        if (*this < other) {
            swap(integer1, integer2);
            swap(fraction1, fraction2);
            sign = '-';
        }

        if (fraction1.size() > fraction2.size())
            fraction2.resize(fraction1.size(), '0');
        else
            fraction1.resize(fraction2.size(), '0');

        for (i = fraction1.size() - 1; i >= 0; --i) {
            int temp = (fraction1[i] - '0') - (fraction2[i] - '0') - borrow;
            if (temp < 0) {
                borrow = 1;
                temp += 10;
            }
            else
                borrow = 0;
            subFrac = to_string(temp) + subFrac;
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
            int temp = (integer1[i] - '0') - (integer2[i] - '0') - borrow;
            if (temp < 0) {
                borrow = 1;
                temp += 10;
            }
            else
                borrow = 0;
            subInt = to_string(temp) + subInt;
        }
    }
    else {
        if (other.sign == '-') {
            second.sign = '+';
            return first + second;
        }else{     
            second.sign = '-';
            return first + second;
        }
    }

    subInt.erase(0, subInt.find_first_not_of('0'));

    if (subInt.empty())
        subInt = "0";
    if (subFrac.empty())
        subFrac = "0";

    return BigReal(sign, subInt, subFrac);
}

ostream& operator << (ostream& out, const BigReal& num){
    if (num.sign == '+')
    {
        out << num.integer << '.' << num.fraction;
    }
    else
    {
        out << num.sign << num.integer << '.' << num.fraction;
    }
    return out;
}




