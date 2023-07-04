#include <stdio.h>
#include <stdlib.h>

struct A {
    char *name;
    int seq;
};

int main(void)
{
    struct A *a = calloc(sizeof(struct A), 10);

    a->name = "Apple";
    a->seq = 1;

    for (int i = 1; i < 10; ++i) {
        a[i] = a[0];
        printf("%s: %d\n", a[i].name, a[i].seq);
    }

    return 0;
}
