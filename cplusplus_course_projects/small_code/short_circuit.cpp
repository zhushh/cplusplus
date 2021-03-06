#include <iostream>
using namespace std;

class Fibonacci {
    public:
        explicit Fibonacci(int n) : num1(1), num2(0) {
            rec(n);
            cout << num2 << endl;
        }
        bool rec(int x) {
            int temp = num1;
            num1 += num2;
            num2 = temp;
            x && rec(x - 1);
            return true;
        }
    private:
        int num1, num2;
};
bool short_circuit(int t) {
    int num;
    cin >> num;
    Fibonacci a(num - 1);
    t && short_circuit(t - 1);
    return true;
}
int main() {
    int t;
    cin >> t;
    short_circuit(t - 1);
    return 0;
}

