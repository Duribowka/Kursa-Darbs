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

    struct stocking items[100];
    int count = 0;

    char line[256];
    struct stocking current = {0};

    while (fgets(line, sizeof(line), fp)) {

        /* Skip empty lines */
        if (line[0] == '\n')
            continue;

        if (mystrncmp(line, "Name:", 5) == 0) {
            char temp[256];
            sscanf(line + 5, " %[^\n]", temp);

            current.name = malloc(mystrlen(temp) + 1);
            mystrcpy(current.name, temp);
        }
        else if (mystrncmp(line, "Genre:", 6) == 0) {
            char temp[256];
            sscanf(line + 6, " %[^\n]", temp);

            current.type = malloc(mystrlen(temp) + 1);
            mystrcpy(current.type, temp);
        }
        else if (mystrncmp(line, "Release date:", 13) == 0) {
            sscanf(line + 13, "%d.%d.%d",
                   &current.date.day,
                   &current.date.month,
                   &current.date.year);
        }
        else if (mystrncmp(line, "Weight:", 7) == 0) {
            sscanf(line + 7, "%d", &current.weight);
        }
        else if (mystrncmp(line, "Price:", 6) == 0) {
            sscanf(line + 6, "%d", &current.price);
        }
        else if (mystrncmp(line, "Width:", 6) == 0) {
            sscanf(line + 6, "%d", &current.width);
        }
        else if (mystrncmp(line, "Height:", 7) == 0) {
            sscanf(line + 7, "%d", &current.height);
        }
        else if (mystrncmp(line, "Author:", 14) == 0) {
            //char value[128];
            char temp[128];
            sscanf(line + 7, " %[^\n]", temp);
            current.author = malloc(mystrlen(temp) + 1);
            mystrcpy(current.author, temp);
            //current.author = my_strdup(value);
        }
        else if (mystrncmp(line, "Stock:", 6) == 0) {
            sscanf(line + 6, "%d", &current.stock);

            /* Finalize item */
            items[count++] = current;
            current = (struct stocking){0};
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("No items found.\n");
        return;
    }

    /* Sorting */
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
        return;
    }

    /* Print */
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

    /* Cleanup */
    for (int i = 0; i < count; i++) {
        free(items[i].name);
        free(items[i].type);
        free(items[i].author);
    }
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