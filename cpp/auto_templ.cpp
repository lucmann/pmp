#include <iostream>

// C++17 allows any possible nontype template parameters using keyword 'auto'
// g++ -std=c++17
template <auto T>
class Message {
    public:
        void print() {
            std::cout << T << '\n';
        }
};

int main() {
    Message<42> i;
    i.print();

    static char const str[] = "hello";
    Message<str> s;
    s.print();
}
