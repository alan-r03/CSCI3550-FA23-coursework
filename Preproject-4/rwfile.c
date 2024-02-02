/*
 * Auth: Alan Ramirez
 * Date: 10-27-23  (Due: 9-5-23)
 * Course: CSCI-3550 (Sec: 002)
 * Desc:  PREPROJECT-04, rwfile().
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE (100*1024*1024)
int inFile;
int inBytes;
int outFile;
int outBytes;
int fCounter; 
char outFName[80];
char *fBuffer = NULL;
void cleanup(void);
void SIGINT_handler(int sig);

void cleanup(void) {
    if (fBuffer != NULL) {
        free(fBuffer);
        fBuffer = NULL;
    }

    if (inFile >= 0) {
        close(inFile);
        inFile = -1;
    }

    if (outFile >= 0) {
        close(outFile);
        outFile = -1;
    }
    return;
}

void SIGINT_handler (int sig) {
    fprintf(stderr, "ERROR: Program interrupted.\n");
    cleanup();
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) { 
    signal(SIGINT, SIGINT_handler);

    if (argc > 1) { 
        for (fCounter = 1; fCounter < argc; ++fCounter) { 

            fBuffer = (char *) malloc(BUFFER_SIZE);
            if (fBuffer == NULL) {
                fprintf(stderr, "ERROR: Could not allocate memory.\n");
                exit(EXIT_FAILURE);
            }
            
            inFile = open(argv[fCounter], O_RDONLY);
            if (inFile <= 0) {
                fprintf(stderr, "ERROR: Failed to open %s\n", argv[fCounter]);
                cleanup();
                exit(EXIT_FAILURE);
            }
            
            printf("Reading: %s...\n", argv[fCounter]);
            inBytes = read(inFile, fBuffer, BUFFER_SIZE);
            if (inBytes < 0) {
                fprintf(stderr, "ERROR: Unable to read file: %s\n", argv[fCounter]);
                cleanup();
                exit(EXIT_FAILURE);
            }
            
            sprintf(outFName, "file-%02d.dat", fCounter);
            outFile = open(outFName, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
            if (outFile < 0) {
                fprintf(stderr, "ERROR: Could not create: %s\n", outFName);
                cleanup();
                exit(EXIT_FAILURE);
            }
            
            printf("Writing: %s\n", outFName);
            outBytes = write(outFile, fBuffer, (size_t) inBytes);
            if (outBytes != inBytes) {
                fprintf(stderr, "ERROR: Error writing to: %s\n", outFName);
                cleanup();
                exit(EXIT_FAILURE);
            }
            
            cleanup();
        }
        
        cleanup();
        exit(EXIT_SUCCESS);
    } else { 
        printf("ERROR: Need to supply one or more files as input. Try again.\n"); 
        exit(EXIT_FAILURE);
    }
    return 0; 
}