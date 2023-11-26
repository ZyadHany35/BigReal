// File: A2_Task2_13,14_20220147_20220501_20220958
// Purpose: Making a Big Real
// Author: Zeyad , Rahaf , Ahmed
// Section: 13,14
// ID: 20220147_20220501_20220958
// TA: Eng.Belal
// Date: 5 nov 2023

#include <iostream>
#include "BigReal.h"
using namespace std;


int main() {
    BigReal n1("1");
    BigReal n2("0.1");
    BigReal n3(n1);
    cout << n1 << endl;
    cout << (n1 + n2) << endl;
    cout << (n1 - n2) << endl;
    cout << (n1 > n2) << endl;
    cout << (n1 < n2) << endl;
    cout << (n1 == n2) << endl;
    cout << (BigReal("11") + BigReal("22")) << endl;
    n1 = n2;
    cout << n1;
    return 0;
}
