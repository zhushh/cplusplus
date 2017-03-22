/***********************************************************************
 *  > File Name: test.cpp
 *  > Author: zhushuhuang
 *  > Mail: zsh5318@gmail.com
 *  > Created Time: Mon 03 Nov 2014 05:03:01 AM CST
***********************************************************************/

#include <iostream>
#include "password_encryption.h"
using namespace std;

int main() {
    string password;
    cin >> password;
    Encryption pass(password);
    cout << pass.getEncodePas() << endl;
    if (pass.isEq(password)) {
        cout << "right password" << endl;
    } else {
        cout << "wrong password" << endl;
    }
    return 0;
}

