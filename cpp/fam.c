#include <stdio.h>

typedef struct A {
    int a;
} A;

// error: flexible array member in a struct with no named members
typedef struct Arr {
    /* int b; */
    A arr[];
} Arr;

int main() {
    Arr a;

    printf("sizeof(a): %lu\n", sizeof(a));
    printf("sizeof(Arr): %lu\n", sizeof(Arr));
}
