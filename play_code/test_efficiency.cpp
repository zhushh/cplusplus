#include <iostream>
#include <ctime>
using namespace std;

struct Node
{
	int num[100000];
};

void testByValue(Node a) { }
void testByReference(Node &a) { }
void testByPointer(Node *a) { }

int main()
{
	time_t startTime, endTime;
	Node n;
	n.num[0] = 2222;
	int maxNum = 1000000;
	int i = maxNum;

	// testByValue starts
	startTime = clock();

	while (i--)
		testByValue(n);

	endTime = clock();
	cout << "testByValue: " << (double)(endTime-startTime) << "ms" << endl;
	// testByValue ends

	i = maxNum;
	// testByReference starts
	startTime = clock();

	while (i--)
		testByReference(n);

	endTime = clock();
	cout << "testByReference: " << (double)(endTime-startTime) << "ms" << endl;
	// testByReference ends

	i = maxNum;
	// testByPointer starts
	startTime = clock();

	while (i--)
		testByPointer(&n);

	endTime = clock();
	cout << "testByPointer: " << (double)(endTime-startTime) << "ms" << endl;
	// testByPointer ends

	return 0;
}

