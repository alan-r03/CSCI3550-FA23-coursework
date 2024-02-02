/*
 * Auth: Alan Ramirez
 * Date: 10-6-23  (Due: 10-8-23)
 * Course: CSCI-3550 (Sec: 002)
 * Desc:  PREPROJECT-03, gethostname().
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ARRAY_SIZE 80

/* with exit statements, the main function will not return anything */
int main(void) { 
    /* declaration 'hostName' is used to store the local hostname. 
    the line below it ensures that the final character is '\0'. */
    char hostName[ARRAY_SIZE];
    hostName[ARRAY_SIZE-1] = '\0';

    /* this if statement both writes the local host name to 'hostName' and 
    checks if there was an error (gethostname() returns -1); if there's an 
    error, it prints an error and then exits with an EXIT_FAILURE. */
    if (gethostname(hostName, ARRAY_SIZE-1) == -1) {
        printf("ERROR: gethostname()\n");
        exit(EXIT_FAILURE);
    }
    /* otherwise, the program prints the local hostname and exits with an EXIT_SUCCESS. */
    printf("Local hostname: %s\n", hostName);
    exit(EXIT_SUCCESS);
}
