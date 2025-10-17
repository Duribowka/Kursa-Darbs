#include "../headers/myFuncts.h"

int main(){

    int num = 5;

    struct stocking stockings[5] = {
        {"Programming for Noobs", "literature", "---", "---", "950g", "---", 23.99, 25.5, 356},
        {"Tomati Kekavas", "vegetables", "---", "---", "200g", "---", 2.89, 10.3, 2537},
        {"K450 keyboard", "electronics", "---", "Kanitronis", "438g", "---", 35.79, 40.25, 178},
        {"Cooking Complect", "instruments", "---", "Jokitchen", "800g", "---", 12.90, 33.6, 96},
        {"Steak", "meat", "---", "Jokitchen", "250g", "---", 8.99, 20, 3589}

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