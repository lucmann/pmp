#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

inline int foo(int b);

int foo(int b) {
    return 3 + b;
}

int main() {
   char *orig_ptr = malloc(1024);
   char *real_ptr = realloc(orig_ptr, 2048);
   char *shri_ptr = realloc(real_ptr, 256);

   printf("orig_ptr = %p\n", orig_ptr);
   printf("real_ptr = %p\n", real_ptr);
   printf("shri_ptr = %p\n", shri_ptr);

   return 0;
}
