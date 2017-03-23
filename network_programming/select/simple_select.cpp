/*************************************************************************
 > File Name: simple_select.cpp
 > Author: zhushh
 > Mail: 
 > Created Time: Thu 23 Mar 2017 03:43:15 PM CST
 ************************************************************************/

#include <iostream>
#include <string>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#define STDIN 0

int main()
{
    struct timeval tv;

    tv.tv_sec = 2;
    tv.tv_usec = 5000;

    fd_set reads;

    FD_ZERO(&reads);
    FD_SET(STDIN, &reads);

    if (select(STDIN+1, &reads, NULL, NULL, &tv) == -1) {
        perror("select");
        exit(1);
    }

    if (FD_ISSET(STDIN, &reads)) 
    {
        std::string input;

        std::cin >> input;
        std::cout << "You input: " << input << std::endl;
    } 
    else 
    {
        printf("Timeout\n");
    }

    return 0;
}

