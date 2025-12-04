#ifndef FILES_H
#define FILES_H

#include "structs.h"

#define DATABASE_FILE "database.txt"
#define TEMP_FILE "temporary.txt"
#define AUTHORS_FILE "authors.txt"

void append_item(struct stocking *s);

void append_author(struct author *a);

void remove_entry(const char *filename, const char *label, const char *target);

void print_entry(const char *filename, const char *label, const char *target);

void edit_entry(const char *filename, const char *entryLabel, const char *entryName, const char *category, const char *newValue);

void print_whole_file(const char *filename);

#endif