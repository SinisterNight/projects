//Dewey Holland

//Desc the program has a predefined size array of 20 the threads are capped at 5, sum calculator is used to partion the array and calculate the sums the main function is used t o create and join the threads on sumcalculator after calculated it will show the total sum to the user.  basic error handling of thread creation and joining are implemented with appriate error handling as requested. it will display the total partial sums, which thread is accessing what element and will also give the new sum per iteration.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
//imports
#define SIZE 20 //predefined array size
#define THREADS 5//predefined number of threads

int array[SIZE];//setting array size
int array[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}; //filling in values
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //create a global mutex lock
int threadSums[THREADS] = {0};//setting threadsums
void *sumCalculator(void *arg) {//start of sumCalculator computes a certain section of the array based on thread identifier.
    int tid = *((int *)arg);//thread identifier
    int start = tid * 4;//start and end are used to partition loop
    int end = start + 3;
    int sum = 0;// sum declaration
    pthread_mutex_lock(&mutex); //lock the mutex,
    for (int i = start; i <= end; i++) {
        sum += array[i]; //set value of sum to array index I
        printf("Thread %d: Adding array[%d] = %d, sum now %d\n", tid, i, array[i], sum);//printing thread, which array it is getting added to, the value and the sum now
    }

    threadSums[tid] = sum; //threadsums[thread identifer] equals sum
    pthread_mutex_unlock(&mutex);//unlock mutex data accessible no longer mutually exclusive use
    printf("Thread %d: Storing sum %d in threadSums[%d]\n", tid, sum, tid);
    return NULL;//return null
}//end sumcalculator
int main() {//start main
    pthread_t threads[THREADS];//declare and array of pthreads threads[5]
    int threadArrayID[THREADS];//declare an int threadArrayID with size 5 or THREADS
    //using for loop for thread creation into an array
    for (int i = 0; i < THREADS; i++) {// i = 0 i<threads or 5
      if(pthread_create(&threads[i], NULL, sumCalculator, &threadArrayID[i]) != 0) {
          fprintf(stderr, "Error creating thread %d\n", i);//error handling
          exit(EXIT_FAILURE); //  handle the error as required
      }
      else{
        threadArrayID[i] = i;
        //thread created successfully
        }
    }//end thread creation loop
    //joining the threads together
    for (int i = 0; i < THREADS; i++) {// I=0 I<threads or 5
      if (pthread_join(threads[i], NULL) != 0) {
        fprintf(stderr, "Error joining thread %d\n", i);//error handling of threads joining
        exit(EXIT_FAILURE); // handle the error as required
        }
      else{
      //joined successfully no further action needed
      }

    }

    int totalSum = 0;//declare totalSum which is the value of the total sums
    printf("Partial sums:\n");//printing partial sums
    for (int i = 0; i < THREADS; i++) {//iterate through the threads or 5 times
        printf("Thread %d: %d\n", i, threadSums[i]);//print thread i, threadSum[i] so thread number and the value that is stored
        totalSum += threadSums[i];//adjusting value of totalSum
    }

    printf("Total sum: %d\n", totalSum);//printing the total sum, sum

    return 0;// return 0
}// end main
