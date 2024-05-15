//Dewey Holland
//DESC a program that runs all of the page replacement algorithms sorts them and shows the percentages of fault rates to the user
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <sstream>



using namespace std;  //  std namespace

//FIFO page replacement algorithm maintains a list of frames and replaces the oldest page when a fault occurs. the counter for faults is incremented it is queue type to keep track of the order in which the pages are brought into memorry
double fifo(const vector<int>& referenceString, int numFrames, int& totalAccesses) {
    list<int> frames;   // List frames
    int pageFaults = 0;  // Counter for faults

    for (int page : referenceString) {//loop
        totalAccesses++;  // Increment total accesses used to get percentage

        // checking if the page is not inside the frame list
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            //if frames size is less than numFrames then pushback page onto frames
            if (frames.size() < numFrames) {
                frames.push_back(page);
            } else {
                // else frames replace the oldest page 
                frames.pop_front();
                frames.push_back(page);
            }
            pageFaults++;  // incrementfault counter
        }
    }

    return static_cast<double>(pageFaults) / totalAccesses * 100.0;  // Calculate page fault rate casted to double
}

//LRU page replacement algorithm keeps track of the reference order of the pages when a fault happens it replaces it with the page that hasnt been used for the longest/max amount of time
double lru(const vector<int>& referenceString, int numFrames, int& totalAccesses) {
    list<int> frames;   // List frames
    int pageFaults = 0;  // Counter faults

    for (int page : referenceString) {//loop
        totalAccesses++;  // Increment total accesses to calculate the percentages

        frames.remove(page);    // Remove page
        frames.push_back(page);  // pushback frames to the end of page

        // If frame size greater than numFrames
        if (frames.size() > numFrames) {
            frames.pop_front(); //popfront
            pageFaults++;  // Increment fault counter
        }
    }

    return static_cast<double>(pageFaults) / totalAccesses * 100.0;  // Calculate page fault rate casted to double
}

//Random page replacement algorithm replaces a random page when a fault occours the percentage may vary since it is completely random
double randomReplacement(const vector<int>& referenceString, int numFrames, int& totalAccesses) {
    vector<int> frames;   // list frames
    int pageFaults = 0;   // Counter faults

    for (int page : referenceString) {//loop
        totalAccesses++;  // Increment total accesses to calculate percentages

        //attempting to find page inside frames
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            // if frames size < numframes add the page to frames
            if (frames.size() < numFrames) {
                frames.push_back(page); //pushback page
            } else {
                // else replace a random page
                int randomIndex = rand() % numFrames; //random index declaration
                frames[randomIndex] = page;
            }
            pageFaults++;  // Increment fault counter
        }
    }

    return static_cast<double>(pageFaults) / totalAccesses * 100.0;  // Calculate page fault rate casted to double
}

//Beladys page replacement algorithm this uses the approach where the system can look ahead to find the oage that will not be  used for the longest amount of time it iterates through frames, predicting the farthest next use and replaces the page accordingly
double beladys(const vector<int>& referenceString, int numFrames, int& totalAccesses) {
    vector<int> frames;   // List  frames 
    int pageFaults = 0;   // Counter for faults

    for (int i = 0; i < referenceString.size(); ++i) {
        int page = referenceString[i]; // Setting page to reference string
        totalAccesses++;  // Increment total accesses to calculate the total percentages

        // Trying to find frames
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            // If frames size < numframes add the page to frames
            if (frames.size() < numFrames) {
                frames.push_back(page); // Frames push back
            } else {
                // Find the page that will not be used for the longest time
                int limits = numeric_limits<int>::max(); 
                int replace = -1;  // Variable to store the page to replace

                // Loop through the frames to find the page with the farthest next use
                for (int j = 0; j < frames.size(); ++j) {
                    int pageIndex = i + 1;  // Index for looking ahead in the reference string
                    //find the next occurrence of the frame in the reference string
                    while (pageIndex < referenceString.size() && referenceString[pageIndex] != frames[j]) {
                        ++pageIndex;//increment page index
                    }

                    // If the page is not referenced anymore replacement
                    if (pageIndex >= referenceString.size()) {
                        replace = frames[j]; //replace with frames i
                        break; //break
                    } else if (pageIndex < limits) {
                        limits = pageIndex;  // Update the limit 
                        replace = frames[j];// replace frames[j]
                    }
                }

                // Replace the page with the farthest 
                auto it = find(frames.begin(), frames.end(), replace);  // Find the iterator for the page to replace if found it will point to element
                *it = page;  // Replace the page
            }
            pageFaults++;  // Increment page fault counter
        }
    }

    // Calculate and return the page fault rate as a percentage
    return static_cast<double>(pageFaults) / totalAccesses * 100.0;
}
struct Comparison {
    string name;//declarations
    double faultRate; //declarations
};

int main() {
    //random number generation
    srand(time(0));

    // Prompt the user for the number of frames
    int numFrames;//declaration
    cout << "Enter the number of frames: ";//print statement
    cin >> numFrames; //input

    // Prompt the user for the reference string
    cout << "Enter the reference string";
    cin.ignore(); //ignore characters in input
    
    vector<int> referenceString;
    int page;
    string inputLine; //setting page inputline getline with cin, inputline istringstream with input line declarations
    getline(cin, inputLine);
    istringstream iss(inputLine);
    
    while (iss >> page) {
        referenceString.push_back(page); //parse input and push back onto reference string
    }

    // If there are no spaces, try to parse each character as a digit
    if (referenceString.empty() && !inputLine.empty()) {
        for (char c : inputLine) {
            if (isdigit(c)) { //this is used to handle if the input is done as a continious string or spaces for exp 123 1 2 3
                referenceString.push_back(c - '0'); //push back onto reference string
            }
        }
    }

    int totalAccesses = 0;//setting to 0 so that each run has the same chance
    
    // Debugging output
    cout << "Reference String: ";
    for (int page : referenceString) {
        cout << page << " "; //print the reference string back
    }
    cout << endl;

    // Store the page fault rates in an array
    double faultRates[4]; //we plan on storing them in ascending order to show which one is fastest
    faultRates[0] = fifo(referenceString, numFrames, totalAccesses);//setting array
    faultRates[1] = lru(referenceString, numFrames, totalAccesses);//setting array
    faultRates[2] = randomReplacement(referenceString, numFrames, totalAccesses);//setting array
    faultRates[3] = beladys(referenceString, numFrames, totalAccesses);// setting array
    Comparison results[] = {
        {"FIFO", faultRates[0]},
        {"LRU", faultRates[1]},
        {"Random", faultRates[2]},
        {"Beladys", faultRates[3]}
    }; //putting them together so i can keep track after the sorting.
    
    sort(results, results + 4, [](const Comparison& a, const Comparison& b) {
        return a.faultRate < b.faultRate; //sorting based on the fault rate
    });
   	cout << "Comparing the fault rates. As shown the lowest rate will be in 0 and the highest will be in 3\n";
    // Print the sorted results
    for (const auto& result : results) {
        cout << result.name << " Page Fault Rate: " << result.faultRate << "%" << endl;
    }
    
    return 0;//return 0 without error
}
