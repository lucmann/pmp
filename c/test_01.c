#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    uint32_t bits = 0;

    bits = (1 << 32) - 1; 

    printf("(1 << 32) - 1 :  0x%08X\n", bits);

    return 0;
}
