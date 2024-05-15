#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define NUMCHILDREN 100
//defining max number of childeren to be 100 don't want to go over that.

//Programming Assignment 1
int main() {
    srand(time(NULL));//seed

    int totalSum = 0;//total
    pid_t childPids[NUMCHILDREN];//childpid
    int childrenExited = 0;//counter for childeren exited

    for (int i = 0; i < NUMCHILDREN; i++) {//creating 100 child
        pid_t pid = fork();//declaration

        if (pid == -1) {//error handling
            perror("fork");//fork error
            exit(1);//exit with termination
        } else if (pid == 0) {
            // This is the child process

            // Execute the child program with the full path
            char randomNumberProgram[] = ""; // path to childprogram removed path
            char *args[] = {randomNumberProgram, NULL};//arg haha

            execve(randomNumberProgram, args, NULL);//execve rnp

            perror("execve");//error handling
            exit(1);//terminate with error
        } else {
            // This is the parent process
            childPids[i] = pid; //setting array to pid
        }
    }

    while (childrenExited < NUMCHILDREN) { //making sure all 100 exit
        int childExitStatus; //declaration
        pid_t exitedPid = waitpid(-1, &childExitStatus, 0);
        //waiting to make sure each child  proccesses all exited
        if (WIFEXITED(childExitStatus)) {
            int childNumber;
            for (childNumber = 0; childNumber < NUMCHILDREN; childNumber++) {
                if (childPids[childNumber] == exitedPid) {//checking if the number of childeren = exited
                    break;//break the loop
                }
            }
            //print exit status with child number and exit status number
            printf("Child %d exited with status %d\n", childNumber, WEXITSTATUS(childExitStatus));
            //adding rng/exit status number
            totalSum += WEXITSTATUS(childExitStatus);//setting value of total sum
            childrenExited++;//incremented childeren exited
            printf("Childeren still running %d\n", NUMCHILDREN-childrenExited);//prints how many child left
        }
    }

    printf("Sum of values: %d\n", totalSum); //print total sum

    return 0;
}
