#include "../headers/myFuncts.h"

void sort(struct stocking array[], int number){

    struct stocking temp;
    for (int i = 0; i < number - 1; i++) {

        for (int j = 0; j < number - i - 1; j++) {

            if (array[j].stock > array[j + 1].stock) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}