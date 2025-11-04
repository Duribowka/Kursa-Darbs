#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>

//NEEDS CHECKING

typedef struct{
    int day;
    int month;
    int year;
}Date;

struct stocking{
    char name[50];
    char type[50];
    Date date;
    int weight;
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
    Date birthdate;
};

#endif