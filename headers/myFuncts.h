#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stocking{
    char name[50];
    char type[50];
    int size;
    int stock;
};

void sort(struct stocking array[], int number);