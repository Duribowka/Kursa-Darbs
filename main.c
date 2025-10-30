#include "../headers/myFuncts.h"

#define database_file "database.txt"
#define temp_file "temporary.txt"
#define authors_file "authors.txt"

//NEEDS CHECKING

int main(int argc, char** argv){

    struct stocking *stockings = malloc(argc * sizeof(struct stocking));
    struct author *authors = malloc(argc * sizeof(struct author));
    //int cnt = atoi(argv[3]);

    for (int cli = 0; cli < argc; cli++){

        int itemor = 0;

        if (mystrcmp(argv[i], "--author") == 0){
            itemor = 1;
        }
        else if (mystrcmp(argv[i], "--item") == 0){
            itemor = 0;
        }
        if (itemor == 0 && mystrcmp(argv[i], "-name") == 0){
            stockings[0].name = argv[i+1];
        }
        else if (itemor == 1 && mystrcmp(argv[i], "-name") == 0){
            authors[0].name = argv[i+1];
        }
        if (mystrcmp(argv[i], "-genre") == 0){
            stockings[0].type = argv[i+1];
        }
        if (itemor == 0 && mystrcmp(argv[i], "-date") == 0){
            stockings[0].date.day = argv[i+1];
            stockings[0].date.month = argv[i+2];
            stockings[0].date.year = argv[i+3];
        }
        else if (itemor == 1 && mystrcmp(argv[i], "-date") == 0){
            authors[0].birthdate.day = argv[i+1];
            authors[0].birthdate.month = argv[i+2];
            authors[0].birthdate.year = argv[i+3];
        }
        if (mystrcmp(argv[i], "-price") == 0){
            stockings[0].price = argv[i+1];
        }
        if (mystrcmp(argv[i], "-weight") == 0){
            stockings[0].weight = argv[i+1];
        }
        if (mystrcmp(argv[i], "-height") == 0){
            stockings[0].height = argv[i+1];
        }
        if (mystrcmp(argv[i], "-width") == 0){
            stockings[0].width = argv[i+1];
        }
        if (mystrcmp(argv[i], "-stock") == 0){
            stockings[0].stock = argv[i+1];
        }
        if (mystrcmp(argv[i], "-author") == 0){
            stockings[0].author == argv[i+1];
        }
        if (itemor == 0 && mystrcmp(argv[i], "--append") == 0){

            FILE *filepoint = fopen(database_file, "a");
            if (filepoint == NULL){
                printf("FAILURE!");
                return 0;
            }
            fprintf(filepoint, "Name: %s\nGenre: %s\nRelease date: %d.%d.%d\nWeight: %s\nPrice: %.2f$\nWidth: %.2f\nHeight: %.2f\nAuthor: %s\nStock: %d\n\n", stockings[0].name, stockings[0].type, stockings[0].date.day, stockings[0].date.month, stockings[0].date.year, stockings[0].weight, stockings[0].price, stockings[0].width, stockings[0].height, stockings[0].author, stockings[0].stock);
        }
        else if (itemor == 1 && mystrcmp(argv[i], "--append") == 0){
            FILE *filepoint = fopen("authors.txt", "a");
            if (filepoint == NULL){
                printf("FAILURE!");
                return 0;             
            }
            fprintf(filepoint, "Author: %s\nStreet: %s\nE-mail: %s\nWeb-page: %s\nPhone number: %s\nCountry: %s\nDate of birth: %d.%d.%d\n\n", authors[i].name, authors[i].street, authors[i].mail, authors[i].website, authors[i].phone, authors[i].country, authors[i].birthdate.day, authors[i].birthdate.month, authors[i].birthdate.year);
        }
    }
    
    if (mystrcmp(argv[1], "--itm") == 0){

        if (mystrcmp(argv[2], "--add") == 0){

            

            for (int i = 0; i<cnt; i++){
                printf("Enter item specifications: ");
                scanf("%s %s %s %s %f %f %f %s %d",stockings[i].name, stockings[i].type, stockings[i].date, stockings[i].weight, &stockings[i].price, &stockings[i].width, &stockings[i].height, stockings[i].author, &stockings[i].stock);
            }

            

            for (int i = 0; i<cnt; i++){
                fprintf(filepoint, "Name: %s\nGenre: %s\nRelease date: %s\nWeight: %s\nPrice: %.2f$\nWidth: %.2f\nHeight: %.2f\nAuthor: %s\nStock: %d\n\n", stockings[i].name, stockings[i].type, stockings[i].date, stockings[i].weight, stockings[i].price, stockings[i].width, stockings[i].height, stockings[i].author, stockings[i].stock);
            }

            fclose(filepoint);
        }
        else if (mystrcmp(argv[2], "--rm") == 0){

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
        
                    if (mystrncmp(line, "Name:", 5) == 0){
                        char currentName[100];
                        sscanf(line + 5, " %[^\n]", currentName);

                        if (mystrcmp(currentName, nameToDelete) == 0){
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
    else if (mystrcmp(argv[1], "--auth") == 0){

        if (mystrcmp(argv[2], "--add") == 0){

            
        
            for (int i = 0; i<cnt; i++){
                printf("Enter author's information: ");
                scanf("%s %s %s %s %s %s %s", authors[i].name, authors[i].street, authors[i].mail, authors[i].website, authors[i].phone, authors[i].country, authors[i].birthdate);
            }

            

            for (int i = 0; i<cnt; i++){
                
            }

            fclose(filepoint);
        }
        else if (mystrcmp(argv[2], "--rm") == 0){

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
        
                    if (mystrncmp(line, "Author:", 7) == 0){
                        char currentName[100];
                        sscanf(line + 7, " %[^\n]", currentName);

                        if (mystrcmp(currentName, nameToDelete) == 0){
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