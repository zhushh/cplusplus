#include <iostream>

using namespace std;

class A {
    public:
        A() : t(0) {}
        void set(int x) const {
            t = x;  // error
        }  // member functions declares const can't modify the object
        int getx() const {
            int x = t;  // ok, didnot modify the object
            return x;
        }
        void output() {
            cout << t << endl;
        }
    private:
        int t;
};

int main() {
    A t1;
    t1.set(2);
    int y = t1.getx();
    cout << y << endl;
    t1.output();
    return 0;
}

