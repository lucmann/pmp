#include <iostream>

typedef void (*FUN)(void);

class Base {
public:
    virtual void f() { std::cout << "Base::f" << std::endl; }
    virtual void g() { std::cout << "Base::g" << std::endl; }
    virtual void h() { std::cout << "Base::h" << std::endl; }
};

int main()
{
    Base b;
    FUN pFun = nullptr;

    std::cout << "Address of V-Table: " << *(long long *)&b << std::endl;
    std::cout << "Address of Base::f: " << *(long long *)*(long long *)&b << std::endl; 

    pFun = (FUN)*((long long *)*(long long *)&b + 0);
    pFun();
    pFun = (FUN)*((long long *)*(long long *)&b + 1);
    pFun();
    pFun = (FUN)*((long long *)*(long long *)&b + 2);
    pFun();

    return 0;
}


