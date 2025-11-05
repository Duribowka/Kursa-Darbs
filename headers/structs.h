#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    int day;
    int month;
    int year;
} Date;

struct stocking {
    char *name;
    char *type;
    Date date;
    int weight;
    float price;
    float width;
    float height;
    char *author;
    int stock;
};

struct author {
    char *name;
    char *street;
    char *mail;
    char *website;
    char *phone;
    char *country;
    Date birthdate;
};

#endif