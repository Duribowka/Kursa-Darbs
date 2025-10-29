#include "mystring.h"
//NEEDS CHECKING
int mystrcmp(char str1, char str2){

    int i = 0;
    //int flag = 0;

    while (str1[i] != 0 && str2[i] != 0){

        if (str1[i] != str2[i]){
            return 1;
        }
    }
    return 0;
}

