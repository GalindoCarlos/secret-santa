#include "choose.h"

int main(int argc, char *argv[]) {
   FILE *info = fopen("info.txt", "r");
   
   char *line = malloc(sizeof(char) * LINE_SIZE);

   // read number of participants

   line = fgets(line, LINE_SIZE, info);
   if (line == NULL) {
      // error
   }
   long long_num_participants = strtol(line, NULL, 10);
   if (long_num_participants == LONG_MIN || long_num_participants == LONG_MAX) {
      //error
   }
   int num_people = (int) long_num_participants;
   struct person *people = malloc(num_people * sizeof(struct person));
   if (people == NULL) {
      //error
   }



   load_people(people, num_people, info, line);
   shuffle_people(people, num_people);
   assign_people(people, num_people);

   for (int i = 0; i < num_people; i++) {
      printf("%s is assigned to %s\n", people[i].name, people[i].assigned->name);
   }


   free_people(people, num_people);

   return 0;
}

void load_people(struct person *people, int num_people, FILE *info, char *line) {

   for (int i = 0; i < num_people; i++) {
      fgets(line, LINE_SIZE, info);
      char *saveptr;
      char *cur_name = strtok_r(line, "\n\t ", &saveptr);
      people[i].name = malloc(strlen(cur_name) + 1);
      people[i].name = strncpy(people[i].name, cur_name, strlen(cur_name));

      char *cur_email = strtok_r(NULL, "\n\t ", &saveptr);
      people[i].email = malloc(strlen(cur_email) + 1);
      people[i].email = strncpy(people[i].email, cur_email, strlen(cur_email));

   }
}

void shuffle_people(struct person *people, int num_people) {
   srand(time(NULL));
   for (int i = 0; i < num_people; i++) {
      int j = rand() % (num_people - i) + i;
      struct person temp = people[i];
      people[i] = people[j];
      people[j] = temp;
   }
}



void assign_people(struct person *people, int num_people) {
   srand(time(NULL));
   int random_shift = rand() % (num_people - 1) + 1;
   for (int i = 0; i < num_people; i++) {
      int assigned_index = (i + random_shift) % num_people;
      people[i].assigned = &(people[assigned_index]);
      people[assigned_index].chosen = true;
   }
}


void free_people(struct person *people, int num_people) {
   for (int i = 0; i < num_people; i++) {
      free(people[i].name);
      free(people[i].email);
   }
   free(people);
}
