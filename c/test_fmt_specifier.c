#include <stdio.h>
#include <string.h>

int main(void)
{
    // Print a string with a fixed width of 10 characters
    printf("%*s\n", 10, "hello");
    printf("%*s\n", 10, "world");
    printf("%-5d\n", 10);
    printf("%.10s\n", "prog x");

    // Print a string longer than the specified width
    printf("%.10s\n", "this is a long string");

    // Print a string with a maximum width of 10 characters
    printf("%10.10s\n", "this is a long string");

    // Print a string with a fixed width of 15 characters and a maximum width of 10 characters
    printf("%15.10s\n", "this is a long string");

    // Print only the last 10 characters of a string
    const char *str = "truncate from left";
    int len = strlen(str);
    if (len > 10) {
        str += (len - 10);
    }
    printf("%s\n", str);

    return 0;
}
