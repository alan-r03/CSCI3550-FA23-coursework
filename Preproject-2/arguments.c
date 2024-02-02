/*
 * Auth: Alan Ramirez
 * Date: 09-29-23  (Due: 10-1-23)
 * Course: CSCI-3550 (Sec: 002)
 * Desc:  PREPROJECT-02, Command-line Arguments.
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]) { 
    /* takes arguments in addition to the file PATH */
    int counter; 
    /* counts the current number of arguments iterated through in the below for loop */

    if (argc > 1) { 
        /* this if branch executes when there are more arguments than just the file name */
        printf("Program Name: \"%s\"\n", argv[0]); 
        /* this print statement prints the file name / file PATH */
        printf("Arguments: %d\n", argc-1); 
        /* this print statement prints the total number of arguments minus 1: argc */
        for (counter = 1; counter < argc; ++counter) { 
            /* this for loop will iterate through all arguments in argv except for the file name */
            printf("argv[%d]: \"%s\"\n", counter, argv[counter]); 
            /* this print statement prints the current argument ^^ */
        }
    } else { 
        /* this else branch executes when there are no arguments other than the file name */
        printf("ERROR: Must supply one or more arguments. Try again.\n"); 
        /* this print statement prints an error when only the file name is supplied */
    }
    return 0; 
    /* standard return 0 */
}
