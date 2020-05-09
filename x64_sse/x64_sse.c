//
// Created by luc on 2020/5/9.
//
#include <stdlib.h>

void get_coords(float * coords)
{
   unsigned x = 42 / 16;
   unsigned y = 43 % 16;

   coords[0] = x + 0.25f;
   coords[1] = y + 0.25f;
   coords[2] = 0;
   coords[3] = 1.0f;
}

int main(int argc, void *argv)
{
   float *coords = (float *)malloc(4 * sizeof(float));

   if (!coords)
   {
      return -1;
   }

   get_coords(coords);

   free(coords);

   return 0;
}

