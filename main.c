#include "../headers/structs.h"
#include "../headers/mystring.h"
#include "../headers/files.h"

#define DATABASE_FILE "database.txt"
#define TEMP_FILE "temporary.txt"
#define AUTHORS_FILE "authors.txt"

void help_entry(){
    printf("Here is list of all flags:\nFor items:\n    -name  <-- set name's value;\n    -type  <-- set category's value;\n    -date  <-- set date's value;\n    -weight  <-- set weight's value;\n    -price  <-- set price's value;\n    -width  <-- set width's value;\n    -height  <-- set height's value;\n    -author  <-- set value of an author in item's description;\n    -stock  <-- set stocking;\n\nFor authors:\n    -name  <-- set name's value;\n    -street  <-- set street's value;\n    -mail  <-- set e-mail's value;\n    -site  <-- set website's value;\n    -phone  <-- set mobile phone's value;\n    -country  <-- set country;\n    -date  <-- set date of birth;\n\nMain flags:\n    --add  <-- append values to database format;\n    --show  <-- show a database block;\n    --edit  <-- edit data in database;\n    --rm  <-- remove database block;\n    --item  <-- program works with items;\n    --author  <-- program works with authors;\n\n*For deeper information see 'README.md'!\n");
}

void print_entry(const char *filename, const char *entryLabel, const char *entryName){
    FILE *fp = fopen(filename, "r");
    if (!fp){
        printf("FAILURE! Could not open %s.\n", filename);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), fp)){

        if (mystrncmp(line, entryLabel, mystrlen(entryLabel)) == 0){

            if (found)
                break;

            char current[100];
            sscanf(line + mystrlen(entryLabel), " %[^\n]", current);
            if (mystrcmp(current, entryName) == 0){
                found = 1;
                printf("%s", line);
            }
            continue;
        }

        if (found){

            int i = 0;
            while (line[i] == ' ' || line[i] == '\t') i++;
            if (line[i] == '\n' || line[i] == '\0')
                continue;

            printf("%s", line);
        }
    }

    fclose(fp);

    if (!found)
        printf("No entry found for '%s'\n", entryName);
}

//HERE STARTS MAIN

int main(int argc, char **argv){
    struct stocking *s = malloc(sizeof(struct stocking));
    struct author *a = malloc(sizeof(struct author));
 
    int isAuthor = 0;

    for (int i = 1; i < argc; i++) {
        if (mystrcmp(argv[i], "--help") == 0){
            help_entry();
        }
        if (mystrcmp(argv[i], "--author") == 0) isAuthor = 1;
        else if (mystrcmp(argv[i], "--item") == 0) isAuthor = 0;

        if (mystrcmp(argv[i], "-name") == 0){
            if (isAuthor){
                a->name = malloc(mystrlen(argv[i+1]) + 1);
                mystrcpy(a->name, argv[i+1]);
            }
            else{
                s->name = malloc(mystrlen(argv[i+1]) + 1);
                mystrcpy(s->name, argv[i+1]);
            }
        }
        else if (mystrcmp(argv[i], "-type") == 0){
            s->type = malloc(mystrlen(argv[i+1]) + 1);
            mystrcpy(s->type, argv[i+1]);
        }
        else if (mystrcmp(argv[i], "-date") == 0) {
            if (isAuthor) {
                a->birthdate.day = myatoi(argv[i+1]);
                a->birthdate.month = myatoi(argv[i+2]);
                a->birthdate.year = myatoi(argv[i+3]);
            } else {
                s->date.day = myatoi(argv[i+1]);
                s->date.month = myatoi(argv[i+2]);
                s->date.year = myatoi(argv[i+3]);
            }
        }
        else if (mystrcmp(argv[i], "-price") == 0) s->price = myatoi(argv[i+1]);
        else if (mystrcmp(argv[i], "-weight") == 0) s->weight = myatoi(argv[i+1]);
        else if (mystrcmp(argv[i], "-height") == 0) s->height = myatoi(argv[i+1]);
        else if (mystrcmp(argv[i], "-width") == 0) s->width = myatoi(argv[i+1]);
        else if (mystrcmp(argv[i], "-stock") == 0) s->stock = myatoi(argv[i+1]);
        else if (mystrcmp(argv[i], "-author") == 0){
            s->author = malloc(mystrlen(argv[i+1]) + 1);
            mystrcpy(s->author, argv[i+1]);
        }
        else if (mystrcmp(argv[i], "-street") == 0){
            a->street = malloc(mystrlen(argv[i+1]) + 1);
            mystrcpy(a->street, argv[i+1]);
        }
        else if (mystrcmp(argv[i], "-mail") == 0){
            a->mail = malloc(mystrlen(argv[i+1]) + 1);
            mystrcpy(a->mail, argv[i+1]);
        }
        else if (mystrcmp(argv[i], "-site") == 0){
            a->website = malloc(mystrlen(argv[i+1]) + 1);
            mystrcpy(a->website, argv[i+1]);
        }
        else if (mystrcmp(argv[i], "-phone") == 0){
            a->phone = malloc(mystrlen(argv[i+1]) + 1);
            mystrcpy(a->phone, argv[i+1]);
        }
        else if (mystrcmp(argv[i], "-country") == 0){
            a->country = malloc(mystrlen(argv[i+1]) + 1);
            mystrcpy(a->country, argv[i+1]);
        }

        else if (mystrcmp(argv[i], "--add") == 0){
            if (isAuthor){
                append_author(a);
            }
            else{
                append_item(s);
            }
        }

        else if (mystrcmp(argv[i], "--rm") == 0) {
            if (isAuthor)
                remove_entry(AUTHORS_FILE, "Author:", argv[i+1]);
            else
                remove_entry(DATABASE_FILE, "Name:", argv[i+1]);
        }
        else if (mystrcmp(argv[i], "--show") == 0) {
            if (isAuthor)
                print_entry(AUTHORS_FILE, "Author:", argv[i+1]);
            else
                print_entry(DATABASE_FILE, "Name:", argv[i+1]);
        }
        else if (mystrcmp(argv[i], "--edit") == 0){
            const char *target = argv[i + 1];
            const char *category = argv[i + 2];
            const char *newValue = argv[i + 3];

            if (isAuthor)
                edit_entry(AUTHORS_FILE, "Author:", target, category, newValue);
            else
                edit_entry(DATABASE_FILE, "Name:", target, category, newValue);
        }
    }

    free(s->name);
    free(s->type);
    free(s->author);
    free(s);

    free(a->name);
    free(a->street);
    free(a->mail);
    free(a->website);
    free(a->phone);
    free(a->country);
    free(a);
    
    return 0;
}