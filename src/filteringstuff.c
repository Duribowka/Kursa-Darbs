#include "../headers/filteringstuff.h"
#include "../headers/mystring.h"
#include "../headers/sortingstuff.h"
#include "../headers/structs.h"

void filter_items_by_genre(const char *genre) {

    FILE *fp = fopen("database.txt", "r");
    if (!fp) {
        printf("Error: Could not open database.txt\n");
        return;
    }

    struct stocking *items = NULL;
    int count = 0;
    int capacity = 0;

    char line[256];
    struct stocking current = {0};

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

            if (current.type && mystrcmp(current.type, genre) == 0) {

                if (count == capacity) {
                    capacity = (capacity == 0) ? 4 : capacity * 2;
                    struct stocking *tmp =
                        realloc(items, capacity * sizeof(struct stocking));
                    if (!tmp) {
                        printf("Memory allocation failed\n");
                        fclose(fp);
                        return;
                    }
                    items = tmp;
                }

                items[count++] = current;
            } else {
                free(current.name);
                free(current.type);
                free(current.author);
            }

            current = (struct stocking){0};
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("No items match genre '%s'\n", genre);
        free(items);
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Name: %s\n", items[i].name);
        printf("Genre: %s\n", items[i].type);
        printf("Release date: %d.%d.%d\n",
               items[i].date.day,
               items[i].date.month,
               items[i].date.year);
        printf("Weight: %dg\n", items[i].weight);
        printf("Price: %d $\n", items[i].price);
        printf("Width: %d cm\n", items[i].width);
        printf("Height: %d cm\n", items[i].height);
        printf("Item's Author: %s\n", items[i].author);
        printf("Stock: %d in stock\n\n", items[i].stock);
    }

    for (int i = 0; i < count; i++) {
        free(items[i].name);
        free(items[i].type);
        free(items[i].author);
    }
    free(items);
}

void filter_authors_by_country(const char *country) {

    FILE *fp = fopen("authors.txt", "r");
    if (!fp) {
        printf("Error: Could not open authors.txt\n");
        return;
    }

    struct author *authors = NULL;
    int count = 0;
    int capacity = 0;

    char line[256];
    struct author current = {0};

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

            if (current.country &&
                mystrcmp(current.country, country) == 0) {

                if (count == capacity) {
                    capacity = (capacity == 0) ? 4 : capacity * 2;
                    struct author *tmp =
                        realloc(authors, capacity * sizeof(struct author));
                    if (!tmp) {
                        printf("Memory allocation failed\n");
                        fclose(fp);
                        return;
                    }
                    authors = tmp;
                }

                authors[count++] = current;
            } else {
                free(current.name);
                free(current.street);
                free(current.mail);
                free(current.website);
                free(current.phone);
                free(current.country);
            }

            current = (struct author){0};
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("No authors match country '%s'\n", country);
        free(authors);
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Author: %s\n", authors[i].name);
        printf("Street: %s\n", authors[i].street);
        printf("E-mail: %s\n", authors[i].mail);
        printf("Web-page: %s\n", authors[i].website);
        printf("Phone number: %s\n", authors[i].phone);
        printf("Country: %s\n", authors[i].country);
        printf("Date of birth: %d.%d.%d\n\n",
               authors[i].birthdate.day,
               authors[i].birthdate.month,
               authors[i].birthdate.year);
    }

    for (int i = 0; i < count; i++) {
        free(authors[i].name);
        free(authors[i].street);
        free(authors[i].mail);
        free(authors[i].website);
        free(authors[i].phone);
        free(authors[i].country);
    }
    free(authors);
}

void filter_and_sort_items(const char *genre, const char *mode) {

    FILE *fp = fopen("database.txt", "r");
    if (!fp) {
        printf("Error: Could not open database.txt\n");
        return;
    }

    struct stocking *items = NULL;
    int count = 0;
    int capacity = 0;

    struct stocking current = {0};
    char line[256];

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

            if (current.type && mystrcmp(current.type, genre) == 0) {

                if (count == capacity) {
                    capacity = (capacity == 0) ? 4 : capacity * 2;
                    struct stocking *tmp =
                        realloc(items, capacity * sizeof(struct stocking));
                    if (!tmp) {
                        printf("Memory allocation failed\n");
                        fclose(fp);
                        return;
                    }
                    items = tmp;
                }

                items[count++] = current;
            } else {
                free(current.name);
                free(current.type);
                free(current.author);
            }

            current = (struct stocking){0};
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("No items match genre '%s'\n", genre);
        free(items);
        return;
    }

    if (mystrcmp(mode, "alphabet") == 0)
        bubble_sort_name(items, count);
    else if (mystrcmp(mode, "stock") == 0)
        bubble_sort_stock(items, count);
    else if (mystrcmp(mode, "price") == 0)
        bubble_sort_price(items, count);
    else if (mystrcmp(mode, "date") == 0)
        bubble_sort_date(items, count);
    else {
        printf("Unknown sort mode: %s\n", mode);
        free(items);
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Name: %s\n", items[i].name);
        printf("Genre: %s\n", items[i].type);
        printf("Release date: %d.%d.%d\n",
               items[i].date.day,
               items[i].date.month,
               items[i].date.year);
        printf("Weight: %dg\n", items[i].weight);
        printf("Price: %d $\n", items[i].price);
        printf("Width: %d cm\n", items[i].width);
        printf("Height: %d cm\n", items[i].height);
        printf("Item's Author: %s\n", items[i].author);
        printf("Stock: %d in stock\n", items[i].stock);

        if (i < count - 1)
            printf("\n");
    }

    for (int i = 0; i < count; i++) {
        free(items[i].name);
        free(items[i].type);
        free(items[i].author);
    }
    free(items);
}

void filter_and_sort_authors(const char *country, const char *mode) {

    FILE *fp = fopen("authors.txt", "r");
    if (!fp) {
        printf("Error: Could not open authors.txt\n");
        return;
    }

    struct author *authors = NULL;
    int count = 0;
    int capacity = 0;

    struct author current = {0};
    char line[256];

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

            if (current.country &&
                mystrcmp(current.country, country) == 0) {

                if (count == capacity) {
                    capacity = (capacity == 0) ? 4 : capacity * 2;
                    struct author *tmp =
                        realloc(authors, capacity * sizeof(struct author));
                    if (!tmp) {
                        printf("Memory allocation failed\n");
                        fclose(fp);
                        return;
                    }
                    authors = tmp;
                }

                authors[count++] = current;
            } else {
                free(current.name);
                free(current.street);
                free(current.mail);
                free(current.website);
                free(current.phone);
                free(current.country);
            }

            current = (struct author){0};
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("No authors found from country '%s'\n", country);
        free(authors);
        return;
    }

    if (mystrcmp(mode, "alphabet") == 0)
        bubble_sort_author_name(authors, count);
    else if (mystrcmp(mode, "date") == 0)
        bubble_sort_author_date(authors, count);
    else {
        printf("Unknown sort mode: %s\n", mode);
        free(authors);
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Author: %s\n", authors[i].name);
        printf("Street: %s\n", authors[i].street);
        printf("E-mail: %s\n", authors[i].mail);
        printf("Web-page: %s\n", authors[i].website);
        printf("Phone number: %s\n", authors[i].phone);
        printf("Country: %s\n", authors[i].country);
        printf("Date of birth: %d.%d.%d\n",
               authors[i].birthdate.day,
               authors[i].birthdate.month,
               authors[i].birthdate.year);

        if (i < count - 1)
            printf("\n");
    }

    for (int i = 0; i < count; i++) {
        free(authors[i].name);
        free(authors[i].street);
        free(authors[i].mail);
        free(authors[i].website);
        free(authors[i].phone);
        free(authors[i].country);
    }
    free(authors);
}