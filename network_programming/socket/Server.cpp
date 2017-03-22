/*************************************************************************
 > File Name: Server.cpp
 > Author: zhushh
 > Mail: 
 > Created Time: Thu 23 Mar 2017 01:39:05 AM CST
 ************************************************************************/

#include <iostream>
using namespace std;

#include "Socket.h"

int main()
{
    Server s(8889);

    while (s.isAccepted())
    {
        // do something here
        string cmd;
        while (s.recvSTR(cmd))
        {
            s.sendSTR(cmd);
        }
    }

    return 0;
}

