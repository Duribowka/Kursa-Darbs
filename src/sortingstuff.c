#include "../headers/sortingstuff.h"
#include "../headers/mystring.h"
#include "../headers/structs.h"

void bubble_sort_name(struct stocking *items, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (mystrcmp(items[j].name, items[j + 1].name) > 0) {
                struct stocking tmp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = tmp;
            }
        }
    }
}

void bubble_sort_stock(struct stocking *items, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (items[j].stock > items[j + 1].stock) {
                struct stocking tmp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = tmp;
            }
        }
    }
}

void bubble_sort_price(struct stocking *items, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (items[j].price > items[j + 1].price) {
                struct stocking tmp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = tmp;
            }
        }
    }
}

void sort_and_print_items(const char *mode) {
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
            current = (struct stocking){0};
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("No items found.\n");
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
        printf("Price: %d$\n", items[i].price);
        printf("Width: %d\n", items[i].width);
        printf("Height: %d\n", items[i].height);
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

void bubble_sort_date(struct stocking items[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            Date d1 = items[j].date;
            Date d2 = items[j + 1].date;

            int swap = 0;

            if (d1.year < d2.year)
                swap = 1;
            else if (d1.year == d2.year && d1.month < d2.month)
                swap = 1;
            else if (d1.year == d2.year &&
                     d1.month == d2.month &&
                     d1.day < d2.day)
                swap = 1;

            if (swap) {
                struct stocking temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_author_name(struct author authors[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (mystrcmp(authors[j].name, authors[j + 1].name) > 0) {
                struct author tmp = authors[j];
                authors[j] = authors[j + 1];
                authors[j + 1] = tmp;
            }
        }
    }
}

void bubble_sort_author_date(struct author authors[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {

            Date d1 = authors[j].birthdate;
            Date d2 = authors[j + 1].birthdate;

            int swap = 0;

            if (d1.year < d2.year)
                swap = 1;
            else if (d1.year == d2.year && d1.month < d2.month)
                swap = 1;
            else if (d1.year == d2.year &&
                     d1.month == d2.month &&
                     d1.day < d2.day)
                swap = 1;

            if (swap) {
                struct author tmp = authors[j];
                authors[j] = authors[j + 1];
                authors[j + 1] = tmp;
            }
        }
    }
}

void sort_and_print_authors(const char *mode) {

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
            current = (struct author){0};
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("No authors found.\n");
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