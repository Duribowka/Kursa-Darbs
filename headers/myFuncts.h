#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stocking{
    char name[50];
    char type[50];
    char date[50];
    char weight[50];
    float price;
    float width;
    float height;
    char author[50];
    int stock;
};

struct author{
    char name[50];
    char street[50];
    char mail[50];
    char website[50];
    char phone[50];
    char country[50];
    char birthdate[50];
};

void sort(struct stocking array[], int number);