#include "../headers/structs.h"
#include "../headers/mystring.h"
#include <string.h>

#define database_file "database.txt"
#define temp_file "temporary.txt"
#define authors_file "authors.txt"

//NEEDS CHECKING

int main(int argc, char** argv){

    struct stocking *stockings = malloc(argc * sizeof(struct stocking));
    struct author *authors = malloc(argc * sizeof(struct author));
    //int cnt = atoi(argv[3]);

    for (int i = 0; i < argc; i++){

        int itemor = 0;

        if (mystrcmp(argv[i], "--author") == 0){
            itemor = 1;
        }
        else if (mystrcmp(argv[i], "--item") == 0){
            itemor = 0;
        }
        if (itemor == 0 && mystrcmp(argv[i], "-name") == 0){
            //stockings[0].name = argv[i+1];
            strcpy(stockings[0].name, argv[i+1]);
        }
        else if (itemor == 1 && mystrcmp(argv[i], "-name") == 0){
            //authors[0].name = argv[i+1];
            strcpy(authors[0].name, argv[i+1]);
        }
        if (mystrcmp(argv[i], "-genre") == 0){
            //stockings[0].type = argv[i+1];
            strcpy(stockings[0].type, argv[i+1]);
        }
        if (itemor == 0 && mystrcmp(argv[i], "-date") == 0){
            stockings[0].date.day = myatoi(argv[i+1]);
            stockings[0].date.month = myatoi(argv[i+2]);
            stockings[0].date.year = myatoi(argv[i+3]);
            
        }
        else if (itemor == 1 && mystrcmp(argv[i], "-date") == 0){
            authors[0].birthdate.day = myatoi(argv[i+1]);
            authors[0].birthdate.month = myatoi(argv[i+2]);
            authors[0].birthdate.year = myatoi(argv[i+3]);
        }
        if (mystrcmp(argv[i], "-price") == 0){
            stockings[0].price = myatoi(argv[i+1]);
        }
        if (mystrcmp(argv[i], "-weight") == 0){
            stockings[0].weight = myatoi(argv[i+1]);
        }
        if (mystrcmp(argv[i], "-height") == 0){
            stockings[0].height = myatoi(argv[i+1]);
        }
        if (mystrcmp(argv[i], "-width") == 0){
            stockings[0].width = myatoi(argv[i+1]);
        }
        if (mystrcmp(argv[i], "-stock") == 0){
            stockings[0].stock = myatoi(argv[i+1]);
        }
        if (mystrcmp(argv[i], "-author") == 0){
            //stockings[0].author == argv[i+1];
            strcpy(stockings[0].author, argv[i+1]);
        }
        if (itemor == 0 && mystrcmp(argv[i], "--append") == 0){

            FILE *filepoint = fopen(database_file, "a");
            if (filepoint == NULL){
                printf("FAILURE!");
                return 0;
            }
            fprintf(filepoint, "Name: %s\nGenre: %s\nRelease date: %d.%d.%d\nWeight: %dg\nPrice: %.2f$\nWidth: %.2f\nHeight: %.2f\nAuthor: %s\nStock: %d in stock\n\n", stockings[0].name, stockings[0].type, stockings[0].date.day, stockings[0].date.month, stockings[0].date.year, stockings[0].weight, stockings[0].price, stockings[0].width, stockings[0].height, stockings[0].author, stockings[0].stock);
        }
        else if (itemor == 1 && mystrcmp(argv[i], "--append") == 0){
            FILE *filepoint = fopen("authors.txt", "a");
            if (filepoint == NULL){
                printf("FAILURE!");
                return 0;             
            }
            fprintf(filepoint, "Author: %s\nStreet: %s\nE-mail: %s\nWeb-page: %s\nPhone number: %s\nCountry: %s\nDate of birth: %d.%d.%d\n\n", authors[i].name, authors[i].street, authors[i].mail, authors[i].website, authors[i].phone, authors[i].country, authors[i].birthdate.day, authors[i].birthdate.month, authors[i].birthdate.year);
        }
        if (mystrcmp(argv[i], "-street") == 0){
            //authors[0].street = argv[i+1];
            strcpy(authors[0].street, argv[i+1]);
        }
        if (mystrcmp(argv[i], "-mail") == 0){
            //authors[0].mail = argv[i+1];
            strcpy(authors[0].mail, argv[i+1]);
        }
        if (mystrcmp(argv[i], "-site") == 0){
            //authors[0].website = argv[i+1];
            strcpy(authors[0].website, argv[i+1]);
        }
        if (mystrcmp(argv[i], "-mail") == 0){
            //authors[0].mail = argv[i+1];
            strcpy(authors[0].mail, argv[i+1]);
        }
        if (mystrcmp(argv[i], "-phone") == 0){
            //authors[0].phone = argv[i+1];
            strcpy(authors[0].phone, argv[i+1]);
        }
        if (mystrcmp(argv[i], "-country") == 0){
            //authors[0].country = argv[i+1];
            strcpy(authors[0].country, argv[i+1]);
        }
        if (itemor == 0 && mystrcmp(argv[i], "--rm") == 0){
            char nameToDelete[50];

            //nameToDelete = argv[i+1];
            strcpy(nameToDelete, argv[i+1]);

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
        else if (itemor == 1 && mystrcmp(argv[i], "--rm") == 0){

            char nameToDelete[50];

            //nameToDelete = argv[i+1];
            strcpy(nameToDelete, argv[i+1]);

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
    return 0;
    }  
}