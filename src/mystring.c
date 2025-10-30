#include "mystring.h"
//NEEDS CHECKING

int mystrcmp(const char *str1, const char *str2){
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

int mystrncmp(const char *str1, const char *str2, unsigned int n){

    unsigned int i = 0;

    while (i < n && str1[i] && (str1[i] == str2[i])){
        i++;
    }

    if (i == n){
        return 0;
    } 

    return (unsigned char)str1[i] - (unsigned char)str2[i];
}
