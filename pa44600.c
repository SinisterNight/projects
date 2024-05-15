//Dewey Holland

//Desc the program creates functions for 5 different disc schedulers, fcfs, sstf scan, c-scan, c-look, and runs them inside of a simulation. The user is prompted for 3 inital head values. it will generate 1000 random cylinder requests from 5000 cylinders.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CYLINDERS 5000
#define CYLINDERREQUESTS 1000
//import statements and also define statements.
// function prototype for the comparison function used by qsort
int compareInt(const void *a, const void *b);

// function to generate random cylinder requests
void generateRequests(int *requests) {
    for (int i = 0; i < CYLINDERREQUESTS; ++i) {
        requests[i] = rand() % CYLINDERS; //setting requests
    }
}

// function to sort cylinder requests
void sortRequests(int *requests) {
    qsort(requests, CYLINDERREQUESTS, sizeof(int), compareInt); //q sort based on the size of cylinderrequests, compareint
}

// Function to print statistics (initial head, head change, algorithm)
void printStats(int startingHead, int headChange, const char *algorithm) { //parameter startinghead. head change, algorithm
    printf("Initial Head: %d, %s Head Change: %d\n", startingHead, algorithm, headChange); //printing the inital head and head change
}

// FCFS first come first serve does not take into account distance, head needs to take.
int diskFCFS(const int *requests, int startingHead) {
    int headChange = 0;//set headChange to 0

    for (int i = 0; i < CYLINDERREQUESTS; ++i) { //irrate cylinderrequests
        headChange += abs(requests[i] - startingHead); //setting headChange to absolute val of  requests- starting head
        startingHead = requests[i]; //set starting head to requests I
    }

    return headChange;//return headchange
}

// SSTF shortest seek time first the purpose of this function is to handle the disc request by the shortest seek time, closest distance to the head, it is required to be sorted so that we can find out the shortest time.
int diskSSTF(const int *requests, int startingHead) {
    int headChange = 0;//set head change to 0
    int visited[CYLINDERREQUESTS] = {0}; // mark requests as visited

    for (int i = 0; i < CYLINDERREQUESTS; ++i) {
        int minimumDistance = CYLINDERS + 1; //min distance = cylinders+1
        int minimumIndex = -1; //set min index to -1

        for (int j = 0; j < CYLINDERREQUESTS; ++j) {//iterate
            if (!visited[j]) {//if visted
                int distance = abs(requests[j] - startingHead);//set distance
                if (distance < minimumDistance) {//if distance < mindistance
                    minimumDistance = distance;//set min distance to distance
                    minimumIndex = j; //set minindex to j.
                }
            }
        }

        headChange += minimumDistance; //setting  the value of head change to calculate the value of the information
        startingHead = requests[minimumIndex];//setting the value of starting head to request min index
        visited[minimumIndex] = 1; // Mark the request as visited
    }

    return headChange;// return headchange
}

// SCAN (ELEVATOR) moves in one direction until the requests are filled then it can return back goes left/right
int diskSCAN(const int *requests, int startingHead) {
    int headChange = 0;//setting headChange tp 0

    //sort the requests
    int sortedRequests[CYLINDERREQUESTS]; //setting sorted requests
    memcpy(sortedRequests, requests, sizeof(int) * CYLINDERREQUESTS);//memcopy for sorted
    qsort(sortedRequests, CYLINDERREQUESTS, sizeof(int), compareInt);//qsort

    //find the index of the starting head in the sorted array
    int index = 0;//setting index
    while (index < CYLINDERREQUESTS && sortedRequests[index] < startingHead) {//index < cylinderrequests and sortedrequest[index] less than starting head
        index++;//increment
    }

    //go left from the starting head
    for (int i = index - 1; i >= 0; --i) {//decrement
        headChange += abs(sortedRequests[i] - startingHead);//adjust headchange to abs sorted request-startinghead
        startingHead = sortedRequests[i];//set starting head to sorted request index
    }

    // go right from the starting head
    for (int i = index; i < CYLINDERREQUESTS; ++i) {//increment
        headChange += abs(sortedRequests[i] - startingHead);//set headchange to abs of sorted request index minus starting head.
        startingHead = sortedRequests[i];//setting the value of the starting head.
    }

    return headChange; // returning headChange.
}

//CSCAN circular scan, completes the trip but instead of servicing on the return requests it will only service on the way there
int diskCSCAN(const int *requests, int startingHead) {
    int headChange = 0;//settting head change to 0
    int distance, currentTrack; //declare distance and currentTrack

    // Sorting requests
    int sortedRequests[CYLINDERREQUESTS]; //setting sorted results
    memcpy(sortedRequests, requests, sizeof(int) * CYLINDERREQUESTS);//mem cpy
    qsort(sortedRequests, CYLINDERREQUESTS, sizeof(int), compareInt);//sort

    // Finding the index where the startingHead is located in the sorted array
    int index = 0;//set index to 0
    while (index < CYLINDERREQUESTS && sortedRequests[index] < startingHead) {
        index++;//increment index
    }

    // Run the SCAN algorithm to the right
    for (int i = index; i < CYLINDERREQUESTS; ++i) {//i less than cylinderequests
        currentTrack = sortedRequests[i]; //setting  current track to the sorted request index
        headChange += abs(currentTrack - startingHead);//set headChange += absolute value of currentrack - startinghead
        startingHead = currentTrack;//setting startingHead to current track.
    }

    // Move to the beginning and continue to the right
    headChange += abs(CYLINDERS - startingHead);//setting headchange to abs value of cylinders- startinghead
    startingHead = 0;//set starting head to 0

    for (int i = 0; i < index; ++i) {
        currentTrack = sortedRequests[i];//current track to sorted requests index
        headChange += abs(currentTrack - startingHead);//set headchange to headchange + abs value of currentTrack-starting head
        startingHead = currentTrack;//set the startingHead
    }

    return headChange;//return headChange
}

// CLOOK head services in one direct and then jumps back to the farthest request in the other direction
int diskCLOOK(const int *requests, int startingHead) {
    int headChange = 0;//set head change
    int distance, currentTrack;//set distance and current track
    int left[CYLINDERREQUESTS], right[CYLINDERREQUESTS];//set left and right
    int leftSize = 0, rightSize = 0;//set leftsize and rightsie

    // separate requests into left and right arrays
    for (int i = 0; i < CYLINDERREQUESTS; i++) {
        if (requests[i] < startingHead)//checking left
            left[leftSize++] = requests[i];
        if (requests[i] > startingHead)
            right[rightSize++] = requests[i];//checking right
    }

    // Sorting left and right arrays
    qsort(left, leftSize, sizeof(int), compareInt);
    qsort(right, rightSize, sizeof(int), compareInt);

    // Service requests on the right side of the head
    for (int i = 0; i < rightSize; i++) {
        currentTrack = right[i];//set current track to right index
        headChange += abs(currentTrack - startingHead);//update value of headChange
        startingHead = currentTrack;//change the value of startingHead to the value of currentTrack
    }

    //jump to the last track that needs to be serviced in the left direction
    headChange += abs(startingHead - left[0]);//setting the value of headChange
    startingHead = left[0];//setStartingHead

    //Service requests on the left side
    for (int i = 0; i < leftSize; i++) {
        currentTrack = left[i];//set currentTrack to leftindex
        headChange += abs(currentTrack - startingHead);//setting the value of headChange
        startingHead = currentTrack;//set starting head to the current track.
    }

    return headChange;//return head change
}




// Comparison function for qsort
int compareInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);//used to handle the sorting
}

// Structure to represent a disk scheduling algorithm
typedef struct {//create struct
    int (*algorithm)(const int *, int); // function pointer for the algorithm
    const char *name; // name of the algorithm
} DiskAlgorithm;//disk aglorithm

int calculateHeadMovement(const int *requests, int startingHead, const DiskAlgorithm *algorithm) {
    if (algorithm->algorithm == diskSSTF || algorithm->algorithm == diskSCAN|| algorithm->algorithm == diskCSCAN|| algorithm->algorithm == diskCLOOK) {//checking if the  algorithm is SSTF, SCAN, CSCAN, CLOOK due to the information needing to be sorted
        int sortedRequests[CYLINDERREQUESTS];//sort requests based off of cylinderrequests
        memcpy(sortedRequests, requests, sizeof(int) * CYLINDERREQUESTS);//mem copy
        qsort(sortedRequests, CYLINDERREQUESTS, sizeof(int), compareInt);//qsort

        return algorithm->algorithm(sortedRequests, startingHead);//return sorted requests, starting head
    } else {
        // FCFS use the original unsorted requests
        return algorithm->algorithm(requests, startingHead);//return reqeusts starting head
    }
}


int main() {
    srand(time(NULL));//seed

    int startingPositions[3]; //set startingPOS
    printf("Enter the first initial head position: ");
    scanf("%d", &startingPositions[0]);//input

    printf("Enter the second initial head position: ");
    scanf("%d", &startingPositions[1]);//input

    printf("Enter the third initial head position: ");
    scanf("%d", &startingPositions[2]);//input

    int requests[CYLINDERREQUESTS];//requests
    generateRequests(requests);//generate cyl requests

    printf("Cylinder Request LOG:\n");//will print all of the requests

    for (int i = 0; i < CYLINDERREQUESTS; ++i) {
        printf("%d ", requests[i]);//loop through requests
    }
    printf("\n");//new line

    // Array of disk scheduling algorithms
    DiskAlgorithm algorithms[] = {
        {diskFCFS, "FCFS"},
        {diskSSTF, "SSTF"},
        {diskSCAN, "SCAN"},
        {diskCSCAN, "C-SCAN"},//setting DiskAlgorithm so we can print information.
        {diskCLOOK, "C-LOOK"},
       
    };

    for (int i = 0; i < sizeof(algorithms) / sizeof(algorithms[0]); ++i) {
        for (int j = 0; j < 3; ++j) {
            int startingHead = startingPositions[j];//set starting head to startingPosition (user input)
            int headChange = calculateHeadMovement(requests, startingHead, &algorithms[i]); //set head change by calling calculate head movement. passed through as starting head but starting head was set to starting POS
            printStats(startingHead, headChange, algorithms[i].name);//print stats starting head, head change, name of algoritm.
        }
    }

    return 0; //exit 0
}
