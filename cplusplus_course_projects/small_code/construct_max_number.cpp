// ����n ��������ÿ������С��1000 
// �������n���������ɳƵ�������� 
// �����������У���һ��Ϊ��������n���ڶ���Ϊn������(�ո����) 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

// compare function for sort
bool compare(string a, string b) {
    return a + b > b + a;    // decreasing sequence
}
int main() {
    int n;
    string num;
    vector<string> arr;
    vector<string>::iterator it;
    cin >> n;
    while (n-- > 0) {
        cin >> num;
        arr.push_back(num);
    }
    sort(arr.begin(), arr.end(), compare);
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i];
    }
    cout << endl;
    return 0;
}

