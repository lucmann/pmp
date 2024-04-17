#include <string>

int main()
{
    std::string s0;

    // invalid operands of types 'const char [4]' and 'const char [4]'
    // to binary 'operator+'
    std::string s1 = "abc" + "def" + '\n';
    std::string s2 = "abc" + ("def" + s0);
}


