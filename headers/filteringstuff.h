#ifndef FILTERINGSTUFF_H
#define FILTERINGSTUFF_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

void filter_items_by_genre(const char *genre);

void filter_authors_by_country(const char *country);

void filter_and_sort_items(const char *genre, const char *mode);

void filter_and_sort_authors(const char *country, const char *mode);

#endif