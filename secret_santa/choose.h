#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// establish some kind of terminology for


// who
struct person {
   bool chosen;
   char* name;
   char* email; 
   struct person *assigned;
};

void load_people(char **info, struct person *people, int num_people);
