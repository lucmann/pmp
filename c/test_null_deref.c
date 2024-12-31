// Copyright (C) 2024 Luc Ma
//
// SPDX-License-Identifier: GPL-2.0
#include <stdio.h>

struct foo {
    long a;
};

int main(int argc, char *argv[])
{
    struct foo *f = NULL;

    printf("0x%016lx\n", &f->a);
}
