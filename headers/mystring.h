#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdio.h>
#include <stdlib.h>

int mystrcmp(const char *str1, const char *str2);

int mystrncmp(const char *str1, const char *str2, unsigned int n);

int myatoi(const char *string);

char *mystrcpy(char *dest, const char *source);

int mystrlen(const char *str);

#endif