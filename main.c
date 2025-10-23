#include "../headers/myFuncts.h"

int main(){

    int cnt;
    char choice;
    printf("Do you want to add an item(I) or an author(A)?\n");
    scanf("%c", &choice);
    
    if (choice == 'I' || choice == 'i'){

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
    }

    else if (choice == 'A' || choice == 'a'){

        printf("How many authors do you want to add?\ninput> ");
        scanf("%d", &cnt);

        struct author *authors = malloc(cnt * sizeof(struct author));

        for (int i = 0; i<cnt; i++){

            printf("Enter author's information: ");
            scanf("%s %s %s %s %s %s %s", authors[i].name, authors[i].street, authors[i].mail, authors[i].website, authors[i].phone, authors[i].country, authors[i].birthdate);
        }

        FILE *filepoint = fopen("authors.txt", "a");
        if (filepoint == NULL){
            printf("FAILURE!");
            return 0;
        }

        for (int i = 0; i<cnt; i++){
            fprintf(filepoint, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n", authors[i].name, authors[i].street, authors[i].mail, authors[i].website, authors[i].phone, authors[i].country, authors[i].birthdate);
        }

        fclose(filepoint);
    }
    

    return 0;
}