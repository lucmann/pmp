#include <iostream>
#include <vector>

template <typename T>
struct is_pointer {
    static const bool value = false;
};

template <typename T>
struct is_pointer<T*> {
    static const bool value = true;
};

int main(int argc, char **argv)
{
    const bool iter_is_ptr = is_pointer<std::vector<int>::iterator>::value;

    std::cout << "vector<int>::iterator is " << (iter_is_ptr ? "" : "not ") << "pointer" << '\n';

    return 0;
}
