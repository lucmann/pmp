#include <stdio.h>

typedef struct A {
    int a;
} A;

// gcc -pedantic complains
typedef struct Arr {
    A arr[0];
} Arr;

int main() {
    Arr a;

    printf("sizeof(a): %lu\n", sizeof(a));
    printf("sizeof(Arr): %lu\n", sizeof(Arr));
}
