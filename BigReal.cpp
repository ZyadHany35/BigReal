#include "BigReal.h"
#include <iostream>
#include <regex>
#include <string>
using namespace std;

bool BigReal::isValidReal(const string& real)
{
    if (regex_match(real, regex("[+-]?\\d*\\.?\\d*"))) 
        return true;

    else  return false;

};

BigReal::BigReal(string real) {
    if (isValidReal(real)) {
        if (real[0] == '-') {
            sign = '-';
            real[0] = '0';
        }
        else if (real[0] == '+') {
            sign = '+';
            real[0] = '0';
        }
        if (regex_search(real, regex("\\."))) { // if has a dot 

            integer = real.substr(0, real.find('.'));
            fraction = real.substr(real.find('.') + 1);
            if (integer.size() == 0) 
                integer = "0";
            if (fraction.size() == 0) 
                fraction = "0";
            
        }
        else {
            if (real.size() == 0)
                integer = "0";
            else
                integer = move(real);
            fraction = "0";
        }
        integer.erase(0, integer.find_first_not_of('0'));
        fraction.erase(fraction.find_last_not_of('0')+1,fraction.size()-1);


        if (integer.empty())
            integer = "0";
        if (fraction.empty())
            fraction = "0";
    }
    else {
        integer = "0"; // if not valid store +0.0
        fraction = "0";
    }
}

void BigReal::setNum(string real) {
    if (isValidReal(real)) {
        if (real[0] == '-') {
            sign = '-';
            real[0] = '0';
        }
        else if (real[0] == '+') {
            sign = '+';
            real[0] = '0';
        }
        if (regex_search(real, regex("\\."))) { // if has a dot 

            integer = real.substr(0, real.find('.'));
            fraction = real.substr(real.find('.') + 1);
            if (integer.size() == 0) 
                integer = "0";
            if (fraction.size() == 0) 
                fraction = "0";
            
        }
        else {
            if (real.size() == 0)
                integer = "0";
            else
                integer = move(real);
            fraction = "0";
        }
        integer.erase(0, integer.find_first_not_of('0'));
        fraction.erase(fraction.find_last_not_of('0')+1,fraction.size()-1);


        if (integer.empty())
            integer = "0";
        if (fraction.empty())
            fraction = "0";
    }
    else {
        integer = "0"; // if not valid store +0.0
        fraction = "0";
    }
}

//BigReal::BigReal(const BigReal& other); // Copy constructor
//BigReal::BigReal& operator= (BigReal& other); // Assignment operator

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

bool BigReal::operator< (const BigReal& anotherReal) {
    if (sign == '+' && anotherReal.sign == '-') {
        return false;
    }
    else if (sign == '-' && anotherReal.sign == '+')
        return true;
    string integer1 = integer, fraction1 = fraction; // to not modify the original real 
    string integer2 = anotherReal.integer, fraction2 = anotherReal.fraction;
    int nonZeroIndex1=0;
    int nonZeroIndex2=0;
    if(integer != "0")
        nonZeroIndex1 = integer1.find_first_not_of('0');
    if(anotherReal.integer != "0")
        nonZeroIndex2 = integer2.find_first_not_of('0');

    // Compare the lengths after removing leading zeros
    int len1 = integer1.length() - nonZeroIndex1;
    int len2 = integer2.length() - nonZeroIndex2;
    bool ifSign = sign == '+' ? true : false;
    if (len1 < len2) {
        return ifSign;
    }
    else if (len1 > len2)
        return !ifSign;

    for (int i = 0; i < len1; ++i) {
        if (integer1[nonZeroIndex1 + i] > integer2[nonZeroIndex2 + i])
            return !ifSign;
        else if (integer1[nonZeroIndex1 + i] < integer2[nonZeroIndex2 + i])
            return ifSign;
    }
    if (fraction1.length() > fraction2.length())
        fraction2.resize(fraction1.length(), '0');
    else if (fraction1.length() < fraction2.length())
        fraction1.resize(fraction2.length(), '0');

    for (int j = 0; j < fraction1.length(); ++j) {
        if (fraction1[j] > fraction2[j])
            return !ifSign;
        else if (fraction1[j] < fraction2[j])
            return ifSign;
    }
    return false;
    
}

bool BigReal::operator> (const BigReal& anotherReal) {
    if (sign == '+' && anotherReal.sign == '-') {
        return true;
    }
    else if (sign == '-' && anotherReal.sign == '+')
        return false;
    string integer1 = integer, fraction1 = fraction; // to not modify the original real 
    string integer2 = anotherReal.integer, fraction2 = anotherReal.fraction;

    int nonZeroIndex1 = 0;
    int nonZeroIndex2 = 0;
    if (integer != "0")
        nonZeroIndex1 = integer1.find_first_not_of('0');
    if (anotherReal.integer != "0")
        nonZeroIndex2 = integer2.find_first_not_of('0');

    // Compare the lengths after removing leading zeros
    int len1 = integer1.length() - nonZeroIndex1;
    int len2 = integer2.length() - nonZeroIndex2;
    bool ifSign = sign == '+' ? false : true;
    if (len1 < len2) 
        return ifSign;
    else if (len1 > len2)
        return !ifSign;

    for (int i = 0; i < len1; ++i) {
        if (integer1[nonZeroIndex1 + i] > integer2[nonZeroIndex2 + i])
            return !ifSign;
        else if (integer1[nonZeroIndex1 + i] < integer2[nonZeroIndex2 + i])
            return ifSign;
    }
    if (fraction1.length() > fraction2.length())
        fraction2.resize(fraction1.length(), '0');
    else if (fraction1.length() < fraction2.length())
        fraction1.resize(fraction2.length(), '0');

    for (int j = 0; j < fraction1.length(); ++j) {
        if (fraction1[j] > fraction2[j])
            return !ifSign;
        else if (fraction1[j] < fraction2[j])
            return ifSign;

    }
    return false;
    
}
bool BigReal::operator== (const BigReal& anotherReal) {
    if (!(*this > anotherReal) && !(*this < anotherReal))
        return true;
    else
        return false;
}

ostream& operator << (ostream& out, const BigReal& num)
{
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

