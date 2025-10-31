#include "../headers/structs.h"
#include "../headers/mystring.h"

#define DATABASE_FILE "database.txt"
#define TEMP_FILE "temporary.txt"
#define AUTHORS_FILE "authors.txt"

void append_item(struct stocking *s) {
    FILE *f = fopen(DATABASE_FILE, "a");
    if (!f) { printf("FAILURE!\n"); return; }
    fprintf(f,
        "Name: %s\nGenre: %s\nRelease date: %d.%d.%d\nWeight: %dg\nPrice: %.2f$\n"
        "Width: %.2f\nHeight: %.2f\nAuthor: %s\nStock: %d in stock\n\n",
        s->name, s->type, s->date.day, s->date.month, s->date.year,
        s->weight, s->price, s->width, s->height, s->author, s->stock
    );
    fclose(f);
}

void append_author(struct author *a) {
    FILE *f = fopen(AUTHORS_FILE, "a");
    if (!f) { printf("FAILURE!\n"); return; }
    fprintf(f,
        "Author: %s\nStreet: %s\nE-mail: %s\nWeb-page: %s\nPhone number: %s\n"
        "Country: %s\nDate of birth: %d.%d.%d\n\n",
        a->name, a->street, a->mail, a->website, a->phone,
        a->country, a->birthdate.day, a->birthdate.month, a->birthdate.year
    );
    fclose(f);
}

void remove_entry(const char *filename, const char *label, const char *target, int skipLines) {
    FILE *in = fopen(filename, "r");
    FILE *out = fopen(TEMP_FILE, "w");

    if (!in || !out) {
        printf("FAILURE CAN'T OPEN FILES\n");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    char line[256];
    int skip = 0;
    while (fgets(line, sizeof(line), in)) {
        if (!skip && mystrncmp(line, label, mystrlen(label)) == 0) {
            char current[100];
            sscanf(line + mystrlen(label), " %[^\n]", current);
            if (mystrcmp(current, target) == 0) {
                skip = skipLines;
                continue;
            }
        }
        if (skip > 0) { skip--; continue; }
        fputs(line, out);
    }

    fclose(in);
    fclose(out);
    remove(filename);
    rename(TEMP_FILE, filename);

    printf("Deleted all data about '%s'.\n", target);
}

int main(int argc, char **argv) {
    struct stocking *s = malloc(sizeof(struct stocking));
    struct author *a = malloc(sizeof(struct author));
    int isAuthor = 0;

    for (int i = 1; i < argc; i++) {
        if (mystrcmp(argv[i], "--author") == 0) isAuthor = 1;
        else if (mystrcmp(argv[i], "--item") == 0) isAuthor = 0;

        if (mystrcmp(argv[i], "-name") == 0)
            mystrcpy(isAuthor ? a->name : s->name, argv[i+1]);
        else if (mystrcmp(argv[i], "-genre") == 0)
            mystrcpy(s->type, argv[i+1]);
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
        else if (mystrcmp(argv[i], "-author") == 0) mystrcpy(s->author, argv[i+1]);
        else if (mystrcmp(argv[i], "-street") == 0) mystrcpy(a->street, argv[i+1]);
        else if (mystrcmp(argv[i], "-mail") == 0) mystrcpy(a->mail, argv[i+1]);
        else if (mystrcmp(argv[i], "-site") == 0) mystrcpy(a->website, argv[i+1]);
        else if (mystrcmp(argv[i], "-phone") == 0) mystrcpy(a->phone, argv[i+1]);
        else if (mystrcmp(argv[i], "-country") == 0) mystrcpy(a->country, argv[i+1]);

        else if (mystrcmp(argv[i], "--append") == 0)
            isAuthor ? append_author(a) : append_item(s);

        else if (mystrcmp(argv[i], "--rm") == 0) {
            const char *target = argv[i+1];
            if (isAuthor)
                remove_entry(AUTHORS_FILE, "Author:", target, 7);
            else
                remove_entry(DATABASE_FILE, "Name:", target, 9);
        }
    }

    free(s);
    free(a);
    return 0;
}