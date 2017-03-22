/*************************************************************************
 > File Name: Client.cpp
 > Author: zhushh
 > Mail: 
 > Created Time: Thu 23 Mar 2017 02:01:54 AM CST
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

#include "Socket.h"

int main()
{
    Client c("127.0.0.1", 8889);
    string cmd;
    while (cin >> cmd) 
    {
        c.sendSTR(cmd);
        c.recvSTR(cmd);
        std::cout << cmd << std::endl;
    }

    return 0;
}

