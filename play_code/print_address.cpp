#include <iostream>
using namespace std;

/*
void mySwap(int a, int b)
{
		cout << "mySwap:\t&a = " << &a << ", \t&b = " << &b << endl;
}
*/
/*
void mySwap(int *a, int *b)
{
	cout << "mySwap:\t&a = " << &a << ", \t&b = " << &b << endl;
	cout << "mySwap:\ta = " << a << ", \tb = " << b << endl;
}
*/
void mySwap(int &a, int &b)
{
		cout << "mySwap:\t&a = " << &a << ", \t&b = " << &b << endl;
}
int main()
{
	int n = 15, m = 20;
	cout << "before:\t&n = " << &n << ", \t&m = " << &m << endl;
	cout << endl;

	cout << "mySwap function called:" << endl;
	// 如果是传指针请用这种方式调用：
	// mySwap(&n, &m);
	mySwap(n, m);
	cout << "mySwap function end:" << endl;

	cout << endl;
	cout << "after:\t&n = " << &n << ", \t&m = " << &m << endl;

	return 0;
}

