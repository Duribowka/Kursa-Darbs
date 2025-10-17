#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stocking{
    char name[50];
    char type[50];
    char date[50];
    char brand[50];
    char weight[50];
    char liters[50];
    float price;
    float size;
    int stock;
};

struct manufacturers{
    char manuname[50];
    char street[50];
    char postal[50];
    char mail[50];
    char website[50];
    char phone[50];
    char country[50];
    char capital[100];
}

void sort(struct stocking array[], int number);