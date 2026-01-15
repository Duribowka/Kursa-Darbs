#include "../headers/mystring.h"

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

int myatoi(const char *string){
    int result = 0;
    int sign = 1;
    int i = 0;

    while(string[i] == ' ' || string[i] == '\t' || string[i] == '\n'){
        i++;
    }

    if (string[i] == '-'){
        sign = -1;
        i++;
    }
    else if (string[i] == '+'){
        i++;
    }

    while (string[i] >= '0' && string[i] <= '9'){
        result = result*10+(string[i] - '0');
        i++;
    }

    return sign * result;
}

char *mystrcpy(char *dest, const char *source){
    char *ptr = dest;

    while (*source != '\0'){
        *dest = *source;
        dest++;     
        source++;
    }
    *dest = '\0';

    return ptr;
}

int mystrlen(const char *str){
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char *my_strdup(const char *src) {
    char *dst = malloc(mystrlen(src) + 1);
    if (dst)
        mystrcpy(dst, src);
    return dst;
}