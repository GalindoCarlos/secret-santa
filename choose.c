#include "choose.h"

/*
 * Contains all main logic components.
 * Reads in information for secret santa game.
 * Allocates space to store information for secret santa game.
 * Does random assignments for secret santa game.
 *
 * Returns 1 if a failure is encountered, 0 otherwise
 */
int main(int argc, char *argv[]) {
   FILE *info = fopen("info.txt", "r");
   if (info == NULL) {
      printf("Error reading information file");
      return 1;
   }
   
   char *line = malloc(sizeof(char) * LINE_SIZE);
   if (line == NULL) {
      printf("Memory allocation error");
      free(line);
      return 1;
   }

   line = fgets(line, LINE_SIZE, info);
   if (line == NULL) {
      printf("Error reading information file");
      free(line);
      return 1;
   }
   long long_num_participants = strtol(line, NULL, 10);
   if (long_num_participants == LONG_MIN || long_num_participants == LONG_MAX) {
      printf("Invalid number of participants");
      free(line);
      return 1;
   }
   int num_people = (int) long_num_participants;
   struct person *people = malloc(num_people * sizeof(struct person));
   if (people == NULL) {
      printf("Memory allocation error");
      free(line);
      free(people);
      return 1;
   }



   load_people(people, num_people, info, line);
   shuffle_people(people, num_people);
   assign_people(people, num_people);

   FILE *res_file = fopen("results.txt", "w");
   if (res_file == NULL) {
      printf("Error creating results");
      free(people);
      free(line);
      return 1;
   }
   for (int i = 0; i < num_people; i++) {
      fprintf(res_file, "%s,%s,%s\n", people[i].name, people[i].email, people[i].assigned->name);
   }
   fclose(res_file); 



   free_people(people, num_people);
   free(line);
   return 0;
}


/*
 * Loads information for a secret santa game into a struct person pointer.
 *
 * Input: 
 * struct person *people - A struct person pointer that points to an array of
 *                         num_people struct persons. Each struct contains
 *                         name and email information for each person
 * int num_people - A integer that classifies that number of people allowed
 *                  in a secret santa game
 * char *line - A char pointer that is intended to point to the current line
 *              being read from the information file
 *
 * Outputs:
 * None, but people is updated with correct game information.
 */
void load_people(struct person *people, int num_people, FILE *info, char *line) {
   for (int i = 0; i < num_people; i++) {

      // store names
      fgets(line, LINE_SIZE, info);
      char *saveptr;
      char *cur_name = strtok_r(line, "\n\t ", &saveptr);
      people[i].name = malloc(strlen(cur_name) + 1);
      if (people[i].name == NULL) {
         printf("Memory allocation error");
         free(line);
         free_people(people, num_people);
         return;
      }
      people[i].name = strncpy(people[i].name, cur_name, strlen(cur_name));

      // store emails
      char *cur_email = strtok_r(NULL, "\n\t ", &saveptr);
      people[i].email = malloc(strlen(cur_email) + 1);
      if (people[i].email == NULL) {
         printf("Memory allocation error");
         free(line);
         free_people(people, num_people);
         return;
      }
      people[i].email = strncpy(people[i].email, cur_email, strlen(cur_email));

   }
}

/*
 * Randomly shuffles the position of people in an array for a
 * secret santa game
 *
 * Inputs:
 * struct person *people - A pointer tha that points to an array
 *                         of struct persons
 * int num_poeple - The number of people in a secret santa game
 *
 * Outputs:
 * None, but people is updated
 */
void shuffle_people(struct person *people, int num_people) {
   srand(time(NULL));
   for (int i = 0; i < num_people; i++) {
      int j = rand() % (num_people - i) + i;
      struct person temp = people[i];
      people[i] = people[j];
      people[j] = temp;
   }
}

/*
 * Performs a random array index shift to generate random assignments
 * for a secret santa game.
 *
 * Inputs:
 * struct person *people - A pointer to an array of struct persons
 *                         that contain information for a secret santa game
 * int num_people - The number of people in a secret santa game
 *
 * Outputs:
 * None, but people is updated with random assignments
 */
void assign_people(struct person *people, int num_people) {
   srand(time(NULL));
   int random_shift = rand() % (num_people - 1) + 1;
   for (int i = 0; i < num_people; i++) {
      int assigned_index = (i + random_shift) % num_people;
      people[i].assigned = &(people[assigned_index]);
      people[assigned_index].chosen = true;
   }
}

/*
 * Frees memory storing information for people in a secret santa game
 *
 * Inputs:
 * struct person *people - A pointer to an array of struct persons
 *                         that contain information for a secret santa game
 * int num_people - The number of people in a secret santa game
 *
 * Outputs:
 * None, but memory is freed
 */
void free_people(struct person *people, int num_people) {
   for (int i = 0; i < num_people; i++) {
      free(people[i].name);
      free(people[i].email);
   }
   free(people);
}
