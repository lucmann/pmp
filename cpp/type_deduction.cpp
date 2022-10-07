#include <iostream>

template <typename T>
T max(const T& a, const T& b)
{
    return b < a ? a : b;
}

int main()
{
    int i = 17;
    double f = 3.4;
    // compilation error: non-const lvalue reference to type 'int'
    // cannot bind to a value of unrelated type 'double'
    int& ir = f;

    // 为什么上面的语句编译报错，而下面的语句编译通过？
    // C++标准规定的，上面的绑定是非法的。原因是 ir 引用了一个 int 类型
    // 对 ir 的操作应该是整数运算，但 f 却是一个双精度浮点数。因此为了确保
    // 让 ir 绑定一个 int 类型的数，编译器把上面的语句变成如下形式：
    //
    // const int temp = f;
    // const int& ir = temp;
    //
    // 这种情况下， ir 绑定了一个“临时量”对象 (temporary object)， 所谓
    // 临时量对象就是当编译器需要一个空间来暂存表达式的求值结果时临时创
    // 建的一个未命名的对象。临时量对象在 C++11 后的值类型 (value categories)
    // 叫做消亡值 (xvalue), c++11后，任何value categories都是下面三种之一
    //  lvalue, xvalue, prvalue
    // 
    // 了解了编译器的操作后，接下来解释为什么C++标准要将上面语句规定为
    // “非法”。上面的语句中，ir 不是常量引用，意味着允许改变 ir 所绑定的对象
    // 的值。但是，此时 ir 实际绑定的对象是一个临时量，而非 f, 也就是说
    // 当 ir 不是一个常量引用时，这种引用类型与所引用对象的类型不匹配
    // 的情况下，已经不可能通过这个引用去修改本来所引用的对象的值了(由于编译器
    // 的操作)。所以C++标准也就把这种行为归为非法了。
    const int& cir = f;

    std::cout << "max(i, ir): " << max(i, ir) << '\n';
    std::cout << "max(i, cir): " << max(i, cir) << '\n';
}
