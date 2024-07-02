// Copyright (C) 2024 Luc Ma
//
// SPDX-License-Identifier: GPL-2.0

#include <stdio.h>

int main(int argc, char *argv[])
{
    const float scale = 0.1f;
    const int width = 129;

    printf("%f * %d = %f\n", scale, width, scale * width);

    return 0;
}
