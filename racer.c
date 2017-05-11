///racer.c
//A thread controlling a small figure that races
//across a character window
//@author Chris Guarini cdg6285@rit.edu
//Implementation of racer.h

//LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//HEADERS
#include "racer.h"
#include "display.h"

//Declarations
char * strncat(char *dest, const char * src, size_t n);

//Length of pause between frames set by initRacers
static long pause;

///initRacers - Do setup work for all racers at the start of the program
///@param : miliseconds - length of pause between steps in animation
void initRacers(long milliseconds){
  pause = milliseconds;//set global static variable
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
  graphic = "~O=";//back of car
  strncat(graphic, name, 6);//Name
  char * carFront = "o>";//front of car
  strncat(graphic, carFront, 3);
  graphic[MAX_CAR_LEN+1] = 0x00;//null terminate
  r->graphic = graphic;
  return r;
}
