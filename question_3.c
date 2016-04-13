/*	CAB202: Tutorial 5
*	Question 3 - Template
*
*	B.Talbot, April 2016
*	Queensland University of Technology
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>

#include "cab202_graphics.h"
#include "cab202_timers.h"
#include "cab202_sprites.h"

/*
* Defines
*/
#define TIMESTEP 50
#define BITMAP_LENGTH 13
#define WIN_PAUSE 3000

/*
* Function declarations
*	- complete the implementation of the first two functions
*	- "perform_race_step()" is complete
*/
void create_racer_bitmap(char** bitmap, int number);
void free_racers(sprite_id* racers, int racer_count);

bool perform_race_step(sprite_id* racers, int racer_count);

/*
* Main function (the implementation is already complete)
*/
int main() {
	// Seed the random number generator - based off the system clock so it's different
    // every time
	time_t t;
	srand((unsigned) time(&t));

	// Initialise the graphics environment
    setup_screen();

	// Initialise and declare all of the variables
	sprite_id* racers = NULL;
	int racer_count = 0;
	bool racing = false;
	timer_id timer = create_timer(TIMESTEP);

	// Main game loop
	while(1) {
		// Draw the current racers (if they exist), and display some useful text
		clear_screen();
		if (racing) {
			draw_string(screen_width()/2-4, screen_height()-1, "RACING...");
			for (int i = 0; i<racer_count; i++) {
				sprite_draw(racers[i]);
			}
		} else {
			draw_string(screen_width()/2-10, screen_height()-1, "WAITING FOR RACERS...");
		}
		show_screen();

		// Perform a race step if we're racing, otherwise wait for an 'r' press
		if (racing) {
			// Perform the race step, and report if we are still racing
			racing = perform_race_step(racers, racer_count);

			// Show a little winner display if we've just finished...
			if (!racing) {
				draw_string(screen_width()/2-12, screen_height()-1, "WINNER, WINNER, WINNER!");
				show_screen();
				timer_pause(WIN_PAUSE);
			}
		} else {
			// Wait for that 'r' key press...
			while (wait_char() != 'r');

			// Time for a new race, free any old racers (if there are any)
			if (racers != NULL) {
				free_racers(racers, racer_count);
			}

			// Allocate the new racers
			racer_count = 3 + rand() % 3;
			racers = malloc(racer_count * sizeof racers);
			for (int i = 0; i<racer_count; i++) {
				char *bitmap = NULL;
				create_racer_bitmap(&bitmap, i);
				racers[i] = sprite_create(0, i*4, 3, 4, bitmap);
			}

			// Let the program know we are know racing
			racing = true;
		}

		// Wait until we should move on to the next iteration
		while(!timer_expired(timer));
	}

	// Cleanup and exit (although we'll never reach here...)
    cleanup_screen();
    return 0;
}

/*
* Function implementations
*/
void create_racer_bitmap(char** bitmap, int number) {
	// TODO in here we have to dynamically allocate some memory for our bitmap
	// (making sure it's the correct size), then put our 'racer' image into the
	// bitmap. It should look like (where x is the racer number passed in):
	// 		 _
	//		| \
	//		|X|
	//		|_/

	//void *malloc(size_t size) 
	bitmap = (char *) malloc(BITMAP_LENGTH * sizeof *bitmap);
	sprintf(bitmap, " _ | \\|%d||_/", number % 10);
}

void free_racers(sprite_id* racers, int racer_count) {
	// TODO free everything to do with your racers. Look in the implementation
	// of main for some hints. A good rule of thumb is whatever you dynamically
	// allocate (i.e. with a malloc), must be met with a free (there is also a
	// sneaking one hiding in sprite library..)
	
	for (int i = 0; i < racer_count; ++i) {
		free(racer[i]->bitmap);
		free(racer[i]);
	}
	free(racer);
	
}

bool perform_race_step(sprite_id* racers, int racer_count) {
	bool racing = true;
	for (int i = 0; i<racer_count; i++) {
		racers[i]->dx = 1 + rand() % 25;
		racers[i]->x += racers[i]->dx * TIMESTEP/1000;
		racing &= racers[i]->x < screen_width()-2;
	}
	return racing;
}
