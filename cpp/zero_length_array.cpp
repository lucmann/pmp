#include <iostream>

struct A {
    int a;
};

// g++ -pedantic complains
struct Arr {
    A arr[0];
};

int main() {
    Arr a;

    std::cout << "sizeof(Arr): " << sizeof(a) << '\n';
}
