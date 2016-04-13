/*	CAB202: Tutorial 5
*	Question 1 - Template
*
*	B.Talbot, April 2016
*	Queensland University of Technology
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "cab202_sprites.h"
#include "cab202_timers.h"

#define LINE_LENGTH 79
#define NUM_PROBS 10
#define FLOAT_THRESH 0.0001

#define STR_PASS "PASSED!"
#define STR_FAIL "FAILED!"

/*
* Function declarations (all of these are already implemented)
*/
double get_osc_y(double* x, double amplitude);
void update_osc_xy(double* x, double *y);

void print_heading(char bkgChar, char* heading, int offset);

/*
* Complete each of these functions correctly to complete the exercise If you are
* correct, the corresponding test will pass. YOU DO NOT HAVE TO MODIFY ANYTHING
* IN THIS FILE, BESIDES THE 10 FUNCTIONS BELOW!!!
*/
int answer_1(int* arg0) {
    // TODO: return the value pointed to by arg0
    return *arg0;
}

int* answer_2(int* arg0) {
    // TODO: return the address of the value pointed to by arg0
    return arg0;
}

double answer_3(sprite_id arg0) {
    // TODO: return the sum of members 'x' and 'dx' for arg0
    return arg0->x + arg0->dx;
}

double answer_4(double* arg0, double* arg1) {
    // TODO: pass arg0 and arg1 into 'get_osc_y()' and return the result
    return get_osc_y(arg0, *arg1);
}

double answer_5(sprite_id* arg0) {
    // TODO: return the sum of members 'y' and 'dy' for sprite_id pointed to by arg0
    return (*arg0)->y + (*arg0)->dy;
}

double answer_6(double arg0, double arg1) {
    // TODO: pass arg0 and arg1 into 'update_osc_xy()', return the updated y value
    update_osc_xy(&arg0, &arg1);
    return arg1;
}

bool* answer_7(sprite_id arg0) {
    // TODO: return the address of the 'is_visible' member of arg0
    return &(arg0->is_visible);
}

double* answer_8(double arg0[]) {
    // TODO: return the address of the 5th value in the arg0 array
    return &arg0[4];
}

double answer_9(double* arg0) {
    // TODO: return the value of the 7th item in array arg0 (assume it is an array)
    return arg0[6];
}

char answer_10(char** arg0) {
    // TODO: return the 3rd char in the array, who's start address is pointed to by arg0
    return *(*arg0+3);
}



int a = 12;
int b = 22;
int* p;
p = &a;

*p -> a -> 12

p = &b;

*p -> b -> 22


/*
* Main - there's no need to look any further. The question is about completing
* the pointer operations above correctly. Yes, hints at the answers are in here,
* but deciphering the hints is more difficult than simply completing the correct
* implementation for the above functions.
*/
int main() {
    // Get some randomness happening to keep things interesting...
    time_t t;
	srand((unsigned) time(&t));

    // Print the title section
    print_heading('~', NULL, 0);
    print_heading('~', "Where, oh where, could my data be?", (LINE_LENGTH-34)/2);
    print_heading('~', NULL, 0);
    printf("\n");

    // Generate all of the data for the questions in a nice chaotic manner
    int p1_a = rand() % 1000000, *p1_b = &p1_a;
    sprite_id p3_a = sprite_create(0, 0, 1, 1, " ");
    p3_a->x = rand() % 100 - 50;
    p3_a->dx = (rand() % 1000000) / 1000.0 - 500.0;
    p3_a->y = rand() % 100 - 50;
    p3_a->dy = (rand() % 1000000) / 1000.0 - 500.0;
    double p4_a = (rand() % 80000) / 1000.0, p4_b = (rand() % 1000000) / 500000.0 - 1.0, *p4_c = &p4_a, *p4_d = &p4_b;
    sprite_id *p5_a = &p3_a;
    double p6_a = (rand() % 80000) / 1000.0, p6_b = (rand() % 24000) / 1000.0, p6_c = p6_a, p6_d = p6_b;
    double p8_a[10];
    p8_a[6] = (rand() % 1000000) / 1000.0 - 500.0;
    char p10_a[10];
    p10_a[2] = rand() % 26 + 65;
    char *p10_b = &(p10_a[0]);
    char **p10_c = &p10_b;

    // Loop through each of the problems: display description, test expected vs actual, display results
    int ex_i, ac_i;
    double ex_d, ac_d;
    void *ex_pt, *ac_pt;
    char ex_c, ac_c;
    bool failed[NUM_PROBS];
    for (int i = 1; i<=NUM_PROBS; i++) {
        switch (i) {
            case 1:
                print_heading('.', "|PROBLEM 1|", 5);
                printf("'answer_1()' receives a 'pointer to an int'. Return the value of the int.\nTesting...\n");
                ex_i = p1_a;
                ac_i = answer_1(p1_b);
                failed[i-1] = !(ex_i == ac_i);
                printf("Expected return:\t%.6d\t\tActual return:\t%.6d\t\t%s\n", ex_i, ac_i, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            case 2:
                print_heading('.', "|PROBLEM 2|", 5);
                printf("'answer_2()' receives a 'pointer to an int'. Return the address of the int.\nTesting...\n");
                ex_pt = &p1_a;
                ac_pt = answer_2(p1_b);
                failed[i-1] = !(ex_pt == ac_pt);
                printf("Expected return:\t%p\tActual return:\t%p\t%s\n", ex_pt, ac_pt, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            case 3:
                print_heading('.', "|PROBLEM 3|", 5);
                printf("'answer_3()' receives a 'sprite_id'. Return the sum of the x and dx members.\nTesting...\n");
                ex_d = p3_a->x+p3_a->dx;
                ac_d = answer_3(p3_a);
                failed[i-1] = !(fabs(ex_d-ac_d) < FLOAT_THRESH);
                printf("Expected return:\t%f\tActual return:\t%f\t%s\n", ex_d, ac_d, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            case 4:
                print_heading('.', "|PROBLEM 4|", 5);
                printf("'answer_4()' receives two 'pointers to ints'. Pass them in that order to\n'get_osc_y()' and return the result.\nTesting...\n");
                ex_d = get_osc_y(p4_c, p4_b);
                ac_d = answer_4(p4_c, p4_d);
                failed[i-1] = !(fabs(ex_d-ac_d) < FLOAT_THRESH);
                printf("Expected return:\t%f\tActual return:\t%f\t%s\n", ex_d, ac_d, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            case 5:
                print_heading('.', "|PROBLEM 5|", 5);
                printf("'answer_5()' receives a 'pointer to a sprite_id'. Return the sum of y and dy.\nTesting...\n");
                ex_d = p3_a->y+p3_a->dy;
                ac_d = answer_5(p5_a);
                failed[i-1] = !(fabs(ex_d-ac_d) < FLOAT_THRESH);
                printf("Expected return:\t%f\tActual return:\t%f\t%s\n", ex_d, ac_d, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            case 6:
                print_heading('.', "|PROBLEM 6|", 5);
                printf("'answer_6()' receives two 'doubles'. Pass them into 'update_osc_xy()', and\nreturn the updated y value.\nTesting...\n");
                update_osc_xy(&p6_a, &p6_b);
                ex_d = p6_b;
                ac_d = answer_6(p6_c, p6_d);
                failed[i-1] = !(fabs(ex_d-ac_d) < FLOAT_THRESH);
                printf("Expected return:\t%f\tActual return:\t%f\t%s\n", ex_d, ac_d, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            case 7:
                print_heading('.', "|PROBLEM 7|", 5);
                printf("'answer_7()' receives a 'sprite_id'. Return the address of the is_visible\nmember.\nTesting...\n");
                ex_pt = &(p3_a->is_visible);
                ac_pt = answer_7(p3_a);
                failed[i-1] = !(ex_pt == ac_pt);
                printf("Expected return:\t%p\tActual return:\t%p\t%s\n", ex_pt, ac_pt, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            case 8:
                print_heading('.', "|PROBLEM 8|", 5);
                printf("'answer_8()' receives an 'array of doubles'. Return the address of the 5th\nvalue in the array.\nTesting...\n");
                ex_pt = &(p8_a[4]);
                ac_pt = answer_8(p8_a);
                failed[i-1] = !(ex_pt == ac_pt);
                printf("Expected return:\t%p\tActual return:\t%p\t%s\n", ex_pt, ac_pt, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            case 9:
                print_heading('.', "|PROBLEM 9|", 5);
                printf("'answer_9()' receives a 'pointer to a double'. Assume this is an array, and\nreturn the value of the 7th member.\nTesting...\n");
                ex_d = p8_a[6];
                ac_d = answer_9(p8_a);
                failed[i-1] = !(fabs(ex_d-ac_d) < FLOAT_THRESH);
                printf("Expected return:\t%f\tActual return:\t%f\t%s\n", ex_d, ac_d, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            case 10:
                print_heading('.', "|PROBLEM 10|", 5);
                printf("'answer_10()' receives a 'double pointer to a char'. Treat this as a\npointer to the address of the start of an array of chars.\nReturn the 3rd char in the array.\nTesting...\n");
                ex_c = p10_a[2];
                ac_c = answer_10(p10_c);
                failed[i-1] = !(ex_c == ac_c);
                printf("Expected return:\t'%c'\t\tActual return:\t'%c'\t\t%s\n", ex_c, ac_c, failed[i-1] ? STR_FAIL : STR_PASS);
                break;
            default:
                return -1;
        }
        print_heading('.', NULL, 0);
        printf("\n\n");

    }

    // Compile the results
    int total = 0;
    for (int i = 0; i<NUM_PROBS; i++) {
        total += failed[i] ? 0 : 1;
    }

    // Print a verbose summary
    char buff[80];
    print_heading('~', NULL, 0);
    sprintf(buff, "Your total score for the problems was: %.2d / %.2d", total, NUM_PROBS);
    print_heading('~', buff, (LINE_LENGTH-46)/2);
    print_heading('~', NULL, 0);
    if (total == NUM_PROBS) {
        sprintf(buff, "You managed to find where all of your missing data was!");
    } else {
        sprintf(buff, "You're still missing some of your data, keep looking...");
    }
    print_heading('~', buff, (LINE_LENGTH-55)/2);
    print_heading('~', NULL, 0);

    // Return
    return 0;
}

/*
* Function implementations
*/
double get_osc_y(double* x, double amplitude) {
    // a sinusoid (sine wave) that goes between -amplitude and +amplitude with a
    // full cycle taking a distance of around 12.5 (4*pi) in the x direction
    return amplitude * sin(0.5*(*x));
}

void update_osc_xy(double* x, double *y) {
    // a sinusoid (sine wave) that goes between -5 and +5 with a full cycle
    // taking a distance of 10 in the x direction
    double amplitude = 5;
    double period = 10;
    *x += 0.5;
    *y = amplitude * sin((2*3.14)/period*(*x));
}

void print_heading(char bkgChar, char *heading, int offset) {
    char buff[LINE_LENGTH+1];
    bool endFound = false;
    for (int i = 0; i<=LINE_LENGTH; i++) {
        if (i == LINE_LENGTH) {
            buff[i] = '\0';
        } else if (heading == NULL) {
            buff[i] = bkgChar;
        } else if (i == offset) {
            buff[i] = ' ';
        } else if (i > offset && !endFound && heading[i-offset-1] == '\0') {
            buff[i] = ' ';
            endFound = true;
        } else if (i > offset && !endFound) {
            buff[i] = heading[i-offset-1];
        } else {
            buff[i] = bkgChar;
        }
    }
    printf("%s\n", buff);
}
