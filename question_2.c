/*	CAB202: Tutorial 5
*	Question 2 - Template
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
#define DESIRED_WIDTH 80
#define DESIRED_HEIGHT 24

#define CHAR_PLAYER '+'
#define CHAR_PLAYER_DEAD 'X'
#define CHAR_SAFE 'o'
#define CHAR_UNSAFE ' '
#define CHAR_LEFT '<'
#define CHAR_RIGHT '>'
#define CHAR_UP '^'
#define CHAR_DOWN 'v'

#define LEVEL_DIFFICULTY 10

#define QUIT_DELAY 2000

/*
* Function declarations:
* - You must complete the implementations of "create_world()" and "perform_jump()"
* - You must correctly call "set_starting_location()" and "process_key_press()" at
*   the marked locations in "main()"
* - The remaining 3 functions are already completed - nothing to be done there
*/
void create_world(char* empty_array);
void perform_jump(int* x, int* y, int* dx, int* dy, int* distance);

void set_starting_location(int* x, int* y, char* world);
void process_key_press(int key_in, int* dx, int* dy, int* distance);

bool screen_size_valid(void);
char get_game_square(void);
char get_direction_char(int dx, int dy);

/*
* Main function:
*   - Checks if the screen size is valid, if not we report this to the user and
*   exit
*   - Sets up our variable (including declaring a correctly sized array)
*   - Sets up the game (creating the world, and setting the player's start position)
*   - Runs the main game loop (draw the game state, process a user's key press, and
*   jump if necessary - ending the game if killed)
*/
int main() {
    // Seed the random number generator - based off the system clock so it's different
    // every time
	time_t t;
	srand((unsigned) time(&t));

    // Initialise the graphics environment
    setup_screen();

    // We are using a static array size, so let's exit if the screen size is not
    // what our array is set up for
    if (!screen_size_valid()) {
        return 0;
    }

    // Setup our variables
    int score = 0, jump_distance = 0, index, x, y, dx, dy;

    // Create our statically sized array
    // TODO 1: declare a statically sized 1 dimensional array "game_world"
    static char game_world[DESIRED_WIDTH * (DESIRED_HEIGHT - 1)];


    // Fill in the game world
    create_world(game_world);

    // Set the player's starting location
    // TODO 3: call the "set_starting_location()" function with x, y, game_world
    set_starting_location(&x, &y, game_world);


    // Main game loop
    while (1) {
        // Draw the world, player, and game information
        for (int i = 0; i<DESIRED_WIDTH*(DESIRED_HEIGHT-1); i++) {
            draw_char(i % DESIRED_WIDTH, i/DESIRED_WIDTH, game_world[i]);
        }
        draw_char(x, y, CHAR_PLAYER);
        draw_formatted(0, DESIRED_HEIGHT-1, "Current direction: %c", get_direction_char(dx, dy));
        draw_formatted(DESIRED_WIDTH-10, DESIRED_HEIGHT-1, "Score: %d", score);

        // Show the screen
        show_screen();

        // Process the user input
        // TODO 4: You must wait for the user to press a key, and correctly pass
        // that key (along with dx, dy, jump_distance) into "process_key_press()"
        process_key_press(wait_char(), &dx, &dy, &jump_distance);


        // Jump if necessary
        if (jump_distance > 0) {
            // Perform the jump
            perform_jump(&x, &y, &dx, &dy, &jump_distance);

            // Check for death, otherwise increment the score and clear the block
            index = y*DESIRED_WIDTH + x;
            if (game_world[index] == CHAR_UNSAFE) {
                // Show where you failed
                draw_char(x, y, CHAR_PLAYER_DEAD);
                show_screen();
                timer_pause(QUIT_DELAY);

                // Print your score and exit
                cleanup_screen();
                printf("Game over. You missed your jump!\nYour score was %d! Quitting...", score);
                return 0;
            } else {
                score++;
                game_world[index] = CHAR_UNSAFE;
            }
        }
    }

    // Cleanup and exit (although we'll never reach here...)
    cleanup_screen();
    return 0;
}

/*
* Function implementations (you must complete the first 2 - the rest are done)
*/
void create_world(char* empty_array) {
    // TODO 2: For each element in the empty_array, assign the character returned
    // from a "get_game_square()" call
    for (int i =0; i < DESIRED_WIDTH * (DESIRED_HEIGHT-1); ++i) {
        empty_array[i] = get_game_square();
    }

}

void perform_jump(int* x, int* y, int* dx, int* dy, int* distance) {
    // TODO 5: Complete the implementation of the following function. It needs to
    // do the following 3 things:
    //  1.  Increment x by distance*dx, and y by distance*dy
    //  2.  Check if we are still within the game bounds, if not place us on the
    //      closest edge
    //  3.  Set the value of the distance variable to 0

    *x += *distance * *dx;
    *y += *distance * *dy;

    int LEFT_BOUND = 0,
        RIGHT_BOUND = DESIRED_WIDTH - 1,
        TOP_BOUND = 0,
        BOTTOM_BOUND = DESIRED_HEIGHT - 2;
    if (*x < LEFT_BOUND) {
        *x = LEFT_BOUND;
    } else if (*x > RIGHT_BOUND) {
        *x = RIGHT_BOUND;
    } else if (*y < TOP_BOUND) {
        *y = TOP_BOUND;
    } else if (*y > BOTTOM_BOUND) {
        *y = BOTTOM_BOUND;
    }

    *distance = 0;
}

void set_starting_location(int* x, int* y, char* world) {
    // Keep getting random array indices, until one is safe (mark the selected
    // coordinate as unsafe in the array - once we are there we can't jump back)
    bool done = false;
    int index;
    while (!done) {
        // Get a random array index within the array's bounds
        index = rand() % (DESIRED_WIDTH*(DESIRED_HEIGHT-1));

        // If the location selected is safe, save the coordinate and finish
        if (world[index] == CHAR_SAFE) {
            done = true;
            *x = index % DESIRED_WIDTH;
            *y = index / DESIRED_WIDTH;
            world[index] = CHAR_UNSAFE;
        }
    }
}

void process_key_press(int key_in, int* dx, int* dy, int* distance) {
    if (key_in == KEY_LEFT) {
        *dx = -1;
        *dy = 0;
    } else if (key_in == KEY_RIGHT) {
        *dx = 1;
        *dy = 0;
    } else if (key_in == KEY_UP) {
        *dx = 0;
        *dy = -1;
    } else if (key_in == KEY_DOWN) {
        *dx = 0;
        *dy = 1;
    } else if (key_in > '0' && key_in <= '9') {
        // Take advantage of the fact numeric characters are sequential...
        *distance = key_in - '0';
    }
}

bool screen_size_valid(void) {
    // Return immediately if dimensions are valid
    if (screen_width() == DESIRED_WIDTH || screen_height() == DESIRED_HEIGHT) {
        return true;
    }

    // Otherwise, clean up the screen and tell the user why we will quit
    cleanup_screen();

    printf("This game requires screen dimensions of %d x %d.\n", DESIRED_WIDTH, DESIRED_HEIGHT);
    printf("Your dimensions (%d x %d) do not match!\n", screen_width(), screen_height());
    printf("Please fix this and run the program again. Exiting...\n");

    return false;
}

char get_game_square(void) {
    // LEVEL_DIFFICULTY controls the frequency of safe squares...
    return (rand() % LEVEL_DIFFICULTY) ? CHAR_UNSAFE : CHAR_SAFE;
}

char get_direction_char(int dx, int dy) {
    // Ternary operators within ternary operators....
    return (abs(dx) > abs(dy)) ?
        ((dx >= 0) ? CHAR_RIGHT : CHAR_LEFT) :
        ((dy >= 0) ? CHAR_DOWN : CHAR_UP);
}
