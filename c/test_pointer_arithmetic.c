#include <stdio.h>


int main() {
    int array[4] = {1, 2, 3, 4};
    int *pi = &array[0];

    char *pc = pi + 2;

    printf("pi : %p\n", pi);
    printf("pc : %p\n", pc);
}
