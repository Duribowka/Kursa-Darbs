#include "../headers/myFuncts.h"

int main(){

    int cnt;

    printf("How many items do you want to add?\ninput> ");
    scanf("%d", &cnt);

    struct stocking *stockings = malloc(cnt * sizeof(struct stocking));

    for (int i = 0; i<cnt; i++){

        printf("Enter item specifications: ");
        scanf("%s %s %s %s %f %f %f %s %d",stockings[i].name, stockings[i].type, stockings[i].date, stockings[i].weight, &stockings[i].price, &stockings[i].width, &stockings[i].height, stockings[i].author, &stockings[i].stock);
    }

    FILE *filepoint = fopen("database.txt", "a");
    if (filepoint == NULL){
        printf("FAILURE!");
        return 0;
    }

    for (int i = 0; i<cnt; i++){
        fprintf(filepoint, "%s\n%s\n%s\n%s\n%2.lf\n%2.lf\n%2.lf\n%s\n%d\n\n", stockings[i].name, stockings[i].type, stockings[i].date, stockings[i].weight, stockings[i].price, stockings[i].width, stockings[i].height, stockings[i].author, stockings[i].stock);
    }

    fclose(filepoint);

    return 0;
}