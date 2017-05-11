///racer.c
//A thread controlling a small figure that races
//across a character window
//@author Chris Guarini cdg6285@rit.edu
//Implementation of racer.h

#define _BSD_SOURCE
//LIBRARIES
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//HEADERS
#include "racer.h"
#include "display.h"

//Declarations
char * strncat(char *dest, const char * src, size_t n);
char * strncpy(char * dest, const char * src, size_t n);

//Length of pause between frames set by initRacers
static long pause;
pthread_mutex_t mutex;

///initRacers - Do setup work for all racers at the start of the program
///@param : miliseconds - length of pause between steps in animation
void initRacers(long milliseconds){
  pause = milliseconds;//set global static variable
  pthread_mutex_init(&mutex, NULL);
}


///makeRacer - Create a new racer.
///
/// @param : name - the string name to show on the display for this racer
///          position - the row in which to race
/// @return : Racer - pointer to dynamically allocated Racer object
Racer * makeRacer( char * name, int position){
  Racer * r = malloc(sizeof(Racer));//malloc racer
  //set racer values
  r->dist = 0;
  r->row = position;
  char * graphic = malloc(MAX_CAR_LEN+1);//car graphic
  char * carBack = "~O=";
  strncpy(graphic,carBack,3);
  strncat(graphic, name, 6);//Name
  char * carFront = "o>";//front of car
  strncat(graphic, carFront, 3);
  graphic[MAX_CAR_LEN+1] = 0x00;//null terminate
  r->graphic = graphic;
  return r;
}

///destroyRacer
///Destroys all dynamically allocated storage for a racer
void destroyRacer ( Racer * r){
  free(r->graphic);
  free(r);
}

///displayRacer
///Displays the racer to the terminal using Display.h
///@param : racer - void * for use by pthreads in run()
void displayRacer(void * racer){
  //lock the critical section
  pthread_mutex_lock(&mutex);
  //loop through graphic
  for(int i = 0; i < MAX_CAR_LENGTH; i++){
    //Set cursor to correct place
    set_cur_pos(r->row+1, r->dist+i);
    //Place that piece of the car
    put(racer->graphic[i]);
  }
  pthread_mutex_unlock(&mutex);
}

///eraseRacer
///Erarses the racer from the screen using Display.h
///@param : racer - void * for use by pthreads in run()
void eraseRacer(void * racer){
  pthread_mutex_lock(&mutex);
  //loop through graphic
  for(int i = 0; i < MAX_CAR_LENGTH; i++){
    //set cursor to correct place
    set_cur_pos(r->row+1, r->dist+i);
    //erase that section of the car
    put(' ');
  }
  pthread_mutex_unlock(&mutex);
}


///Run one racer in the race
///Initialize the display of the racer's graphic and run the racer thread.
///@param : racer - the racer to simulate
void * run(void * racer){
  //Initialize racer on display
  displayRacer(racer);
  while(1){
    //Calculate random waiting period between 0 and initial delay value
    long wait = (rand() % pause);
    if(wait <= 3){
      racer->graphic[1] = 'X';
      displayRacer(racer);
      destroyRacer(racer);
      pthread_exit(NULL);
      return;
    }
    usleep(wait*1000);//sleep for wait milliseconds
  
    //advance foward by one 
    eraseRacer(racer);//erase current display of racer
    racer->dist++;//advance by 1
    displayRacer(racer);//display racer in new position
    
    //End condition of thread
    if(racer->dist >= FINISH_LINE){
      //Racer at finish line
      destroyRacer(racer);
      pthread_exit(NULL);
      return;
    }
  }
}














