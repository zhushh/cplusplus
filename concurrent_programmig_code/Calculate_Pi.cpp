/*************************************************************************
 > File Name: Calculate_Pi.cpp
 > Author: zhushh
 > Mail: 
 > Created Time: Wed 22 Mar 2017 07:31:53 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <time.h>
#include <pthread.h>

long number_of_thread;
long number_of_toss;
long number_of_count;

pthread_mutex_t mutex;
long sum;

#define IF_COND_EXIT(cond, str, status) \
if (cond)                       \
{                               \
    std::cout << str;           \
    exit(status);               \
}

double randomNumber();
void* count(void*);

int main(int argc, char** argv)
{
    IF_COND_EXIT(argc != 3, "Usage: ./a.out number_of_toss number_of_thread\n", 0);

    number_of_toss   = atoi(argv[1]);
    number_of_thread = atoi(argv[2]);
    number_of_count  = number_of_toss / number_of_thread;

    pthread_t* handlers;
    handlers = (pthread_t*)malloc(number_of_thread * sizeof(pthread_t));

    IF_COND_EXIT(handlers == NULL, "malloc pthread_t fail!\n", 0);

    for (long i = 0; i < number_of_thread; i++)
    {
        pthread_create(&handlers[i], NULL, count, (void*)i);
    }

    for (long i = 0; i < number_of_thread; i++)
    {
        pthread_join(handlers[i], NULL);
    }

    std::cout << "Calculate result: Pi = " << 4*(sum / (double)number_of_toss) << "\n";

    free(handlers);
    return 0;
}

void* count(void* threadId) 
{
    double x, y;
    long number_of_sum = 0;
    long number_of_start = ((long)threadId) * number_of_count;
    for (long i = 0; i < number_of_count; i++)
    {
        if (i+number_of_start >= number_of_toss)
        {
            break;
        }

        x = randomNumber();
        y = randomNumber();

        if (x*x + y*y <= 1)
        {
            number_of_sum++;
        }
    }

    pthread_mutex_lock(&mutex);
    sum += number_of_sum;
    pthread_mutex_unlock(&mutex);
    return (void*)NULL;
}

#include <random>

double randomNumber()
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<double> distribution(-1, 1);
    return distribution(rng);
}

