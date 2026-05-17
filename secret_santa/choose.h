#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define LINE_SIZE 100
// establish some kind of terminology for


// who
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
