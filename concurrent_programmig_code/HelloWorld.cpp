/*************************************************************************
 > File Name: helloWorld.cpp
 > Author: zhushh
 > Mail: 
 > Created Time: Wed 22 Mar 2017 03:59:45 PM CST
 ************************************************************************/

#include <iostream>
#include <thread>
using namespace std;

void hello() 
{
    std::cout << "Hello, Concurrent world!\n";
}

int main()
{
    std::thread t(hello);
    t.join();
    return 0;
}
