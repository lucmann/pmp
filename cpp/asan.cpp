#include <cstdio>
#include <cstring>
#include <memory>

int main() {
    char const* src{"Hello World!"};
    // since c++14
    /* auto const dst{ std::make_unique<char[]>(std::strlen(src)) }; */

    // since c++98, zero-initialized array
    auto const dst{ std::unique_ptr<char>(new char[std::strlen(src)]()) };

    std::strcpy(dst.get(), src);
    std::puts(dst.get());
}
