#include "../headers/myFuncts.h"

#define database_file "database.txt"
#define temp_file "temporary.txt"
#define authors_file "authors.txt"

//NEEDS CHECKING

int main(int argc, char** argv){

    int cnt = atoi(argv[3]);
    
    if (strcmp(argv[1], "--itm") == 0){

        if (strcmp(argv[2], "--add") == 0){

            struct stocking *stockings = malloc(cnt * sizeof(struct stocking));

            for (int i = 0; i<cnt; i++){
                printf("Enter item specifications: ");
                scanf("%s %s %s %s %f %f %f %s %d",stockings[i].name, stockings[i].type, stockings[i].date, stockings[i].weight, &stockings[i].price, &stockings[i].width, &stockings[i].height, stockings[i].author, &stockings[i].stock);
            }

            FILE *filepoint = fopen(database_file, "a");
            if (filepoint == NULL){
                printf("FAILURE!");
                return 0;
            }

            for (int i = 0; i<cnt; i++){
                fprintf(filepoint, "Name: %s\nGenre: %s\nRelease date: %s\nWeight: %s\nPrice: %.2f$\nWidth: %.2f\nHeight: %.2f\nAuthor: %s\nStock: %d\n\n", stockings[i].name, stockings[i].type, stockings[i].date, stockings[i].weight, stockings[i].price, stockings[i].width, stockings[i].height, stockings[i].author, stockings[i].stock);
            }

            fclose(filepoint);
        }
        else if (strcmp(argv[2], "--rm") == 0){

            char nameToDelete[50];

            for (int i = 0; i<cnt; i++){
                printf("Item that you want to delete: ");
                scanf(" %s", nameToDelete);

                FILE *in = fopen(database_file, "r");
                FILE *out = fopen(temp_file, "w");

                if (!in || !out){
                    printf("FAILURE CAN'T OPEN FILES\n");
                    if (in) fclose(in);
                    if (out) fclose(out);
                    return 0;
                }

                char line[100];
                int skipNext = 0;

                while (fgets(line, sizeof(line), in)){
        
                    if (strncmp(line, "Name:", 5) == 0){
                        char currentName[100];
                        sscanf(line + 5, " %[^\n]", currentName);

                        if (strcmp(currentName, nameToDelete) == 0){
                        skipNext = 9;
                        continue;
                        }
                    }

                    if (skipNext > 0){
                        skipNext--;
                        continue;
                    }

                    fputs(line, out);
                }
                fclose(in);
                fclose(out);

                remove(database_file);
                rename(temp_file, database_file);

                printf("Deleted all data about '%s'.\n", nameToDelete);
            }
        }    
    }
    else if (strcmp(argv[1], "--auth") == 0){

        if (strcmp(argv[2], "--add") == 0){

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
        else if (strcmp(argv[2], "--rm") == 0){

            char nameToDelete[50];

            for (int i = 0; i<cnt; i++){
                printf("Author that you want to delete: ");
                scanf(" %s", nameToDelete);

                FILE *in = fopen(authors_file, "r");
                FILE *out = fopen(temp_file, "w");

                if (!in || !out){
                    printf("FAILURE CAN'T OPEN FILES\n");
                    if (in) fclose(in);
                    if (out) fclose(out);
                    return 0;
                }

                char line[100];
                int skipNext = 0;

                while (fgets(line, sizeof(line), in)){
        
                    if (strncmp(line, "Author:", 7) == 0){
                        char currentName[100];
                        sscanf(line + 7, " %[^\n]", currentName);

                        if (strcmp(currentName, nameToDelete) == 0){
                        skipNext = 7;
                        continue;
                        }
                    }

                    if (skipNext > 0){
                        skipNext--;
                        continue;
                    }

                    fputs(line, out);
                }
                fclose(in);
                fclose(out);

                remove(authors_file);
                rename(temp_file, authors_file);

                printf("Deleted all data about '%s'.\n", nameToDelete);
            }
        }    
    }
    else{
        printf("WRONG INPUT GET OUT");
        return 0;
    }
    
    return 0;
}