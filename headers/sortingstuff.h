#ifndef SORTINGSTUFF_H
#define SORTINGSTUFF_H

#include <stdio.h>
#include <stdlib.h>
#include <../headers/structs.h>

void bubble_sort_name(struct stocking *items, int count);

void bubble_sort_stock(struct stocking *items, int count);

void bubble_sort_price(struct stocking *items, int count);

void sort_and_print_items(const char *mode);

void bubble_sort_date(struct stocking items[], int count);

void bubble_sort_author_name(struct author authors[], int count);

void bubble_sort_author_date(struct author authors[], int count);

void sort_and_print_authors(const char *mode);

#endif