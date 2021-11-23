#include <iostream>

using namespace std;

struct empty_struct {};
class empty_class {};

int main()
{
    cout << "A empty struct's footprint is " << sizeof(empty_struct) << "\n";
    cout << "A empty class's footprint is " << sizeof(empty_class) << "\n";

    return 0;
}
