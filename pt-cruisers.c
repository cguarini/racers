///pt-cruisers.c
///Main function for racer threads
///@author Chris Guarini - cdg6285@rit.edu
///Based on racer.h by James Heliotis
///CS243 HW8

//LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//HEADERS
#include "racer.h"//interface of this implementation
#include "display.h"//given code for displaying the racers
#include "queue.h"


//Declarations
int isdigit( int c);
long int strtol(const char *str, char **endptr, int base);
size_t strlen(const char *str);
char * strncpy(char * dest, const char * src, size_t n);


///destroyQueue
///Destroys the queue of names of racers
void destroyQueue(queue * q){
  while(queue_size(q)){
    char * n = dequeue(q);
    free(n);//free malloced names
  }
  destroy_queue(q);//free queue struct
}

///main
///Initializes the random number generator
///and gathers command line arguments to turn into the race
int main(int argc, char * argv[]){
  //initialize random number generator
  srand(time(NULL)); //Seed of current UNIX time
  
  //Check for arguments
  if(argc < 3){//Print usage
    fprintf(stderr, "Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
    return EXIT_FAILURE;
  }

  //Gather arguments
  //Check for max speed delay
  long maxspeed = DEFAULT_WAIT;
  char ** endptr;
  queue q = init_queue;//for racer names
  int nameIndex = 2;//index of where names begin in arguments

  if(isdigit(argv[1][0])){//floating points too maybe
    maxspeed = strtol(argv[1], endptr, 10);//grab max speed
  }
  else{
    nameIndex = 1;//Is a racer name, move index down 1
  }

  //Grab racer names
  //loop through the arguments
  for(int i = nameIndex; i < argc; i++){
    //check if racer name is of correct size
    if(strlen(argv[i]) < MAX_CAR_LEN+1){
      //malloc a space for the name on the heap
      char * n = malloc(MAX_CAR_LEN+1);
      int nullFound = 0;//for use in nested loop
      strncpy(n, argv[i], MAX_CAR_LEN+1);//copy name into malloced space
      for(int j = 0; j < MAX_CAR_LEN; j++){//loop through name to add dashes
        if(n[j] == 0x00){
          nullFound = 1;
          n[j] = '-';
        }
        if(nullFound){
          n[j] = '-';
        }
      }
      n[MAX_CAR_LEN+1] = 0x00;//null terminate
      enqueue(q, n, 0);//enqueue the name
    }
    else{
      fprintf(stderr, "Error: racer names must not exceed length 6.\n");
      destroyQueue(q);
      return EXIT_FAILURE;
    }
  }
  if(queue_size(q) < 2){
    fprintf(stderr, "Usage: pt-cruisers [max-speed-delay] name1 name2 [name3...]\n");
    destroyQueue(q);
    return EXIT_FAILURE;
  }



}





























