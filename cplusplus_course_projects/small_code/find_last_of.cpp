// ���ַ���longer��Ѱ���ַ���shorter�������ַ��������ֵ��ַ��� 

#include <iostream>
#include <string>
using namespace std;
int main() {
	string::size_type loc1, loc2;
	string longer("That is a funny hat.");
	string shorter("hat");
	loc1 = longer.find_last_of(shorter);
	loc2 = longer.find_last_of("any");
	cout << "loc1 position is: " << loc1 << endl;
	cout << "loc2 position is: " << loc2 << endl;
	return 0;
}

