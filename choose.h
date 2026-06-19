#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// Maximum length for a line in an information file
#define LINE_SIZE 100

/*
 * A struct holding various information for a person
 * in a secret santa game
 *
 * bool chosen - indicates if this person has already
 *               been assigned to someone else
 * char *name - the person's name
 * char *email - the person's email
 * struct person *assigned - a pointer to the person this person
 *                           has been assigned to
 */
struct person {
   bool chosen;
   char* name;
   char* email; 
   struct person *assigned;
};

void load_people(struct person *people, int num_people, FILE *info, char *line);
void shuffle_people(struct person *people, int num_people);
void assign_people(struct person *people, int num_people);
void free_people(struct person *people, int num_people);
