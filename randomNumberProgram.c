#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//defining max number of childeren to be 100 don't want to go over that.
//Programming Assignment 1
int main() {
    srand(time(NULL)); // Seed the random number generator

    int randomNum = rand() % 100 + 1; // Generate a random number between 1 and 100

    // Generate a random delay between 200 and 600 microseconds
    int delayMicroseconds = (rand() % 401) + 200;
    usleep(delayMicroseconds);//usleep delay


    return randomNum; // Exit with the random number as the exit status
}
