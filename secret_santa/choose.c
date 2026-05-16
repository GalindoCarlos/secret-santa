#include "choose.h"

int main(int argc, char *argv[]) {
   printf("Got here");
   int num_people = 3;

   struct person *people = malloc(num_people * sizeof(struct person));

   // function to populate people array
   char *some_info[] = {"Carlos", "carlosgalindo@utexas.edu", "Bob", "bob@utexas.edu", "James", "james@utexas.edu"};


   printf("Got here2");


   char **info = some_info;

   load_people(info, people, num_people);

   for (int i = 0; i < num_people; i++) {
      printf("\nPerson %d, name is %s, email is %s\n", i, people[i].name, people[i].email);
   }

   //free(people);

   return 1;
}



void load_people(char **info, struct person *people, int num_people) {
  //every index of info is a word
  
  //format is going to be [name1, email1, name2, email2, ..., nameN, emailN]
 
  for (int i = 0; i < num_people; i++) {
     //hello
     people[i].name = malloc(strlen(info[2 * i]) + 1);
     people[i].email = malloc(strlen(info[2 * i + 1]) + 1);
     people[i].name = strncpy(people[i].name, info[2 * i], strlen(info[2 * i]) + 1);
     people[i].email = strncpy(people[i].email, info[2 * i + 1], strlen(info[2 * i + 1]) + 1);
  }
  
}
