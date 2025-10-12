#include "../headers/myFuncts.h"

int main(){

    int num = 5;

    struct stocking stockings[5] = {
        {"book", "literature", 10, 55},
        {"vegetables", "consumable", 20, 1673},
        {"croissant", "consumable", 15, 137},
        {"pants", "equipment", 35, 48},
        {"knife", "weapon", 25, 23}

    };

    for (int i = 0; i<num; i++){

        printf("------------\nitem: %s\ntype: %s\nsize: %d\nstock: %d\n------------\n\n", stockings[i].name, stockings[i].type, stockings[i].size, stockings[i].stock);
    }

    sort(stockings, num);

    printf("---------SORTING---------\n\n");

    for (int i = 0; i<num; i++){

        printf("------------\nitem: %s\ntype: %s\nsize: %d\nstock: %d\n------------\n\n", stockings[i].name, stockings[i].type, stockings[i].size, stockings[i].stock);
    }

    int cnt = 3;
    struct stocking *stockings2 = malloc(cnt * sizeof(struct stocking));

    for (int i = 0; i<cnt; i++){

        printf("Enter item specifications: ");
        scanf("%s %s %d %d", stockings2[i].name, stockings2[i].type, &stockings2[i].size, &stockings2[i].stock);
    }

    printf("\n---------Printing elements of dynamic array---------\n\n");

    for (int i = 0; i<cnt; i++){
        printf("------------\nitem: %s\ntype: %s\nsize: %d\nstock: %d\n------------\n\n", stockings2[i].name, stockings2[i].type, stockings2[i].size, stockings2[i].stock);
    }

    return 0;
}