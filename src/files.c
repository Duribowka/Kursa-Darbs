#include <stdio.h>
#include <stdlib.h>
#include "../headers/structs.h"
#include "../headers/mystring.h"
#include "../headers/files.h"

void append_item(struct stocking *s) {
    FILE *fp = fopen(DATABASE_FILE, "a");
    if (!fp) {
        printf("FAILURE!\n");
        return;
    }
    fprintf(fp,
        "Name: %s\nGenre: %s\nRelease date: %d.%d.%d\nWeight: %dg\nPrice: %.2f$\n"
        "Width: %.2f\nHeight: %.2f\nAuthor: %s\nStock: %d in stock\n\n",
        s->name, s->type, s->date.day, s->date.month, s->date.year,
        s->weight, s->price, s->width, s->height, s->author, s->stock
    );
    fclose(fp);
}

void append_author(struct author *a) {
    FILE *fp = fopen(AUTHORS_FILE, "a");
    if (!fp) {
        printf("FAILURE!\n");
        return;
    }
    fprintf(fp,
        "Author: %s\nStreet: %s\nE-mail: %s\nWeb-page: %s\nPhone number: %s\n"
        "Country: %s\nDate of birth: %d.%d.%d\n\n",
        a->name, a->street, a->mail, a->website, a->phone,
        a->country, a->birthdate.day, a->birthdate.month, a->birthdate.year
    );
    fclose(fp);
}

void remove_entry(const char *filename, const char *label, const char *target) {
    FILE *in = fopen(filename, "r");
    FILE *out = fopen(TEMP_FILE, "w");

    if (!in || !out) {
        printf("FAILURE CAN'T OPEN FILES\n");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    char line[256];
    int skipping = 0;

    while (fgets(line, sizeof(line), in)) {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t') i++;

        if (skipping && (
            mystrncmp(line + i, "Name:", 5) == 0 ||
            mystrncmp(line + i, "Author:", 7) == 0
        )) {
            skipping = 0;
        }

        if (!skipping && mystrncmp(line + i, label, mystrlen(label)) == 0) {
            char current[128];
            sscanf(line + i + mystrlen(label), " %[^\n]", current);
            if (mystrcmp(current, target) == 0) {
                skipping = 1;
                continue;
            }
        }

        if (!skipping)
            fputs(line, out);
    }

    fclose(in);
    fclose(out);
    remove(filename);
    rename(TEMP_FILE, filename);

    printf("Deleted all data about '%s'.\n", target);
}
