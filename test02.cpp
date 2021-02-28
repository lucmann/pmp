#include <iostream>

using namespace std;

class HasPtrMem {
public:
    HasPtrMem(): d(new int(0)) {}
    HasPtrMem(HasPtrMem& h): d(new int(*h.d)) {}

    ~HasPtrMem() { delete d; }

public:
    int *d;
};

int main()
{
    HasPtrMem a;
    HasPtrMem b(a);
    HasPtrMem& c = a;
    HasPtrMem d = c;

    cout << *a.d << "\n";
    cout << *b.d << "\n";
    cout << *c.d << "\n";
    cout << *d.d << "\n";

    return 0;
}
