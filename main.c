#include "../headers/myFuncts.h"

int main(int argc, char** argv){

    int cnt = atoi(argv[3]);
    
    if (strcmp(argv[1], "item") == 0){

        if (strcmp(argv[2], "append") == 0){

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
                fprintf(filepoint, "Item's name: %s\nGenre: %s\nRelease date: %s\nWeight: %s\nPrice: %.2f$\nWidth: %.2f\nHeight: %.2f\nAuthor: %s\nStock: %d\n\n", stockings[i].name, stockings[i].type, stockings[i].date, stockings[i].weight, stockings[i].price, stockings[i].width, stockings[i].height, stockings[i].author, stockings[i].stock);
            }

            fclose(filepoint);
        }
        else if (strcmp(argv[2], "remove") == 0){
            
        }
    }

    else if (strcmp(argv[1], "author") == 0){

        if (strcmp(argv[2], "append") == 0){

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
                fprintf(filepoint, "Author: %s\nStreet: %s\nE-mail: %s\nWeb-page: %s\nPhone number: %s\nCountry: %s\nDate of birth: %s\n\n", authors[i].name, authors[i].street, authors[i].mail, authors[i].website, authors[i].phone, authors[i].country, authors[i].birthdate);
            }

            fclose(filepoint);
        }
    }
    else{
        printf("WRONG INPUT GET OUT");
        return 0;
    }
    
    return 0;
}