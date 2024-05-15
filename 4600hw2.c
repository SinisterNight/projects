//Dewey Holland
//HW2 pt1
// This program follows the directions of question number 3 to the best of my ability comments are included on just about every step to describe what is happening through the program. This section covers before a mutex lock is added so that the threads can run concurrently while not starting a race condition. that being said no lock is being used in this section this is part 1 of number 3
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//imports
#define FILENAME "randomnumber.txt" //define file name randomnumber.txt

// global variable for the file
FILE* file;

// gunction for reading and writing to the file
void* process(void* arg) { //method creation for process
    int pid = *((int*)arg);//pid declaration
    for (int i = 0; i < 200; i++) {//iterate 0 200
        file = fopen(FILENAME, "r+");//open filename with read/write
        int n;//int n declare
        fscanf(file, "%d", &n);//reads from file, stores to n
        printf("process %d: read in %d from the file\n", pid, n); //printing processes read from the file
        n++;//increment n
        fseek(file, 0, SEEK_SET);//ensures file starts from the start so that when fprintf is ran it overwrites correctly.
        fprintf(file, "%d", n);//writes updated value of n back to file
        fclose(file);//close file
        printf("process %d: wrote %d to the file\n", pid, n);//print process wrote from file
    }//end loop
    return NULL;//return null
}//end method

int main() {//main
    // Initialize the file with an initial value
    file = fopen(FILENAME, "w");//open with write
    fprintf(file, "%d", 0);//set to value of 0 before any read or writing done
    fclose(file);//close file

    // Create three threads for each process
    pthread_t t1, t2, t3;//thread creation 1 2 3
    int pid1 = 1, pid2 = 2, pid3 = 3; //int pid declarations
    //thread create
    pthread_create(&t1, NULL, process, &pid1); //pthread creation t1 pointer, null, process, pid1 pointer
    pthread_create(&t2, NULL, process, &pid2);//pthread creation t2 pointer, null, process, pid2 pointer
    pthread_create(&t3, NULL, process, &pid3);// pthread creation t3, null, process, pid3 pointer
    // wait for all threads to finish creating
    pthread_join(t1, NULL);//join thread
    pthread_join(t2, NULL);//join thread
    pthread_join(t3, NULL);//join thread

    // print the final result
    file = fopen(FILENAME, "r");//open file read mode
    int result;//declaration
    fscanf(file, "%d", &result);//the final results read in
    printf("Final value in the file is: %d\n", result);//print the final value
    fclose(file);//fclose file

    return 0;//return 0
}//end main
