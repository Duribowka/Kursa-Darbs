#include "../headers/filteringstuff.h"
#include "../headers/mystring.h"

void filter_items_by_genre(const char *genre) {
    FILE *fp = fopen("database.txt", "r");
    if (!fp) {
        printf("Error: Could not open database.txt\n");
        return;
    }

    char line[256];
    struct stocking current = {0};
    int match;

    while (fgets(line, sizeof(line), fp)) {

        if (line[0] == '\n')
            continue;

        char *p = line;
        while (*p == ' ' || *p == '\t')
            p++;

        if (mystrncmp(p, "Name:", 5) == 0) {
            char temp[256];
            sscanf(p + 5, " %[^\n]", temp);
            current.name = my_strdup(temp);
        }
        else if (mystrncmp(p, "Genre:", 6) == 0) {
            char temp[256];
            sscanf(p + 6, " %[^\n]", temp);
            current.type = my_strdup(temp);
        }
        else if (mystrncmp(p, "Release date:", 13) == 0) {
            sscanf(p + 13, "%d.%d.%d",
                   &current.date.day,
                   &current.date.month,
                   &current.date.year);
        }
        else if (mystrncmp(p, "Weight:", 7) == 0) {
            sscanf(p + 7, "%d", &current.weight);
        }
        else if (mystrncmp(p, "Price:", 6) == 0) {
            sscanf(p + 6, "%d", &current.price);
        }
        else if (mystrncmp(p, "Width:", 6) == 0) {
            sscanf(p + 6, "%d", &current.width);
        }
        else if (mystrncmp(p, "Height:", 7) == 0) {
            sscanf(p + 7, "%d", &current.height);
        }
        else if (mystrncmp(p, "Item's Author:", 14) == 0) {
            char temp[256];
            sscanf(p + 14, " %[^\n]", temp);
            current.author = my_strdup(temp);
        }
        else if (mystrncmp(p, "Stock:", 6) == 0) {
            sscanf(p + 6, "%d", &current.stock);

            match = (current.type && mystrcmp(current.type, genre) == 0);

            if (match) {
                printf("Name: %s\n", current.name);
                printf("Genre: %s\n", current.type);
                printf("Release date: %d.%d.%d\n",
                       current.date.day, current.date.month, current.date.year);
                printf("Weight: %dg\n", current.weight);
                printf("Price: %d $\n", current.price);
                printf("Width: %d cm\n", current.width);
                printf("Height: %d cm\n", current.height);
                printf("Item's Author: %s\n", current.author);
                printf("Stock: %d in stock\n\n", current.stock);
            }

            free(current.name);
            free(current.type);
            free(current.author);
            current = (struct stocking){0};
        }
    }

    fclose(fp);
}

void filter_authors_by_country(const char *country) {
    FILE *fp = fopen("authors.txt", "r");
    if (!fp) {
        printf("Error: Could not open authors.txt\n");
        return;
    }

    char line[256];
    struct author current = {0};
    int match;

    while (fgets(line, sizeof(line), fp)) {

        if (line[0] == '\n')
            continue;

        char *p = line;
        while (*p == ' ' || *p == '\t')
            p++;

        if (mystrncmp(p, "Author:", 7) == 0) {
            char temp[256];
            sscanf(p + 7, " %[^\n]", temp);
            current.name = my_strdup(temp);
        }
        else if (mystrncmp(p, "Street:", 7) == 0) {
            char temp[256];
            sscanf(p + 7, " %[^\n]", temp);
            current.street = my_strdup(temp);
        }
        else if (mystrncmp(p, "E-mail:", 7) == 0) {
            char temp[256];
            sscanf(p + 7, " %[^\n]", temp);
            current.mail = my_strdup(temp);
        }
        else if (mystrncmp(p, "Web-page:", 9) == 0) {
            char temp[256];
            sscanf(p + 9, " %[^\n]", temp);
            current.website = my_strdup(temp);
        }
        else if (mystrncmp(p, "Phone number:", 13) == 0) {
            char temp[256];
            sscanf(p + 13, " %[^\n]", temp);
            current.phone = my_strdup(temp);
        }
        else if (mystrncmp(p, "Country:", 8) == 0) {
            char temp[256];
            sscanf(p + 8, " %[^\n]", temp);
            current.country = my_strdup(temp);
        }
        else if (mystrncmp(p, "Date of birth:", 14) == 0) {
            sscanf(p + 14, "%d.%d.%d",
                   &current.birthdate.day,
                   &current.birthdate.month,
                   &current.birthdate.year);

            match = (current.country &&
                     mystrcmp(current.country, country) == 0);

            if (match) {
                printf("Author: %s\n", current.name);
                printf("Street: %s\n", current.street);
                printf("E-mail: %s\n", current.mail);
                printf("Web-page: %s\n", current.website);
                printf("Phone number: %s\n", current.phone);
                printf("Country: %s\n", current.country);
                printf("Date of birth: %d.%d.%d\n\n",
                       current.birthdate.day,
                       current.birthdate.month,
                       current.birthdate.year);
            }

            free(current.name);
            free(current.street);
            free(current.mail);
            free(current.website);
            free(current.phone);
            free(current.country);
            current = (struct author){0};
        }
    }

    fclose(fp);
}