/*************************************************************************
 > File Name: Random.cpp
 > Author: zhushh
 > Mail: 
 > Created Time: Wed 22 Mar 2017 08:12:13 PM CST
 ************************************************************************/

#include <iostream>
#include <random>
using namespace std;

int main()
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);
    std::cout << dist6(rng) << std::endl;
    
    std::uniform_real_distribution<double> distribution(-1, 1);
    std::cout << distribution(rng) << std::endl;
    return 0;
}

