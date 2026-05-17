#include "choose.h"

int main(int argc, char *argv[]) {
   int num_people = 3;

   struct person *people = malloc(num_people * sizeof(struct person));

   // function to populate people array
   char *some_info[] = {"Carlos", "carlosgalindo@utexas.edu", "Bob", "bob@utexas.edu", "James", "james@utexas.edu"};


   char **info = some_info;

   load_people(info, people, num_people);
   
   assign_people(people, num_people);

   for (int i = 0; i < num_people; i++) {
      printf("%s is assigned to %s\n", people[i].name, people[i].assigned->name);
   }


   free_people(people, num_people);

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


void assign_people(struct person *people, int num_people) {
   srand(time(NULL));
   for (int i = 0; i < num_people; i++) {
      while (true) {
         int assigned_index = rand() % num_people;
	 if (assigned_index != i && !people[assigned_index].chosen) {
            people[assigned_index].chosen = true;
	    people[i].assigned = &(people[assigned_index]);
	    break;
	 }
      }
   }
}


void free_people(struct person *people, int num_people) {
   for (int i = 0; i < num_people; i++) {
      free(people[i].name);
      free(people[i].email);
   }
   free(people);
}
