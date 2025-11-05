#include "../headers/structs.h"
#include "../headers/mystring.h"
#include "../headers/files.h"

#define DATABASE_FILE "database.txt"
#define TEMP_FILE "temporary.txt"
#define AUTHORS_FILE "authors.txt"

void print_entry(const char *filename, const char *label, const char *target){
    FILE *fp = fopen(filename, "r");
    if (!fp){
        printf("Failed to open %s!\n", filename);
        return;
    }

    char line[256];
    int printing = 0;

    while (fgets(line, sizeof(line), fp)){
        
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t') i++;

        if (printing && (
            mystrncmp(line + i, "Name:", 5) == 0 ||
            mystrncmp(line + i, "Author:", 7) == 0))
        {
            break;
        }

        if (!printing && mystrncmp(line + i, label, mystrlen(label)) == 0){
            char current[128];
            sscanf(line + i + mystrlen(label), " %[^\n]", current);

            if (mystrcmp(current, target) == 0) {
                printing = 1;
                printf("%s", line);
                continue;
            }
        }

        if (printing)
            printf("%s", line);
    }

    fclose(fp);

    if (!printing){
        printf("No entry found for '%s'.\n", target);
    }
}

int main(int argc, char **argv){
    struct stocking *s = malloc(sizeof(struct stocking));
    struct author *a = malloc(sizeof(struct author));

    s->name = malloc(100);
    s->type = malloc(100);
    s->author = malloc(100);

    a->name = malloc(100);
    a->street = malloc(100);
    a->mail = malloc(100);
    a->website = malloc(100);
    a->phone = malloc(100);
    a->country = malloc(100);

    int isAuthor = 0;

    for (int i = 1; i < argc; i++) {
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