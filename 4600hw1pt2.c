#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//THIS PROGRAM ALLOWS FOR USER INPUT MEANING IT SATISFIES PART 2/B because I had selected 4 bytes to but for the program it is dynamic
//Dewey Hollad
// Define constants for file sizes
#define FILESIZE1MB (1024 * 1024)
#define MAXFILESIZE (128 * 1024 * 1024)
#define MAX_TEST_CASES 8
//define max filesize 1mb for easier calculation and max test cases being 128mb or 8  "doubles"
int main() {
    // Filenames for source and destination files
    const char *sourceFilename = "/nfs/home/STUDENTS/dah0318/testfile.txt";
    const char *destFilename = "/nfs/home/STUDENTS/dah0318/copiedfile.txt";

    // Prompt the user for the chunk size
    size_t chunkSize;
    do {
        printf("Enter the chunk size (1 or even number, in bytes): ");//needs to enter 1 or even  number
        scanf("%lu", &chunkSize);//user input

        if (chunkSize != 1 && chunkSize % 2 != 0) {//checking value of user input
            printf("Chunk size must be 1 or an even number. Please try again.\n");//try again
        }
    } while (chunkSize != 1 && chunkSize % 2 != 0);//loop

    // Print header
    printf("Time (s)\n");

    int maxTestCases = MAX_TEST_CASES; // Maximum number of test cases
    double *results = (double *)malloc(maxTestCases * sizeof(double)); // Dynamic array

    if (results == NULL) {
        perror("Failed to allocate memory for results array");//error handle
        return EXIT_FAILURE;//exit with termination
    }

    int resultIndex = 0;//declaration

    for (size_t fileSize = FILESIZE1MB; fileSize <= MAXFILESIZE && resultIndex < maxTestCases; fileSize *= 2) {//checking if the file exists, if not it creates the file,
        FILE *sourceFile = fopen(sourceFilename, "wb");//open source file
        if (sourceFile == NULL) {
            perror("Failed to create/open source file");//error handle
            return EXIT_FAILURE;//terminate with error
        }

        for (size_t i = 0; i < fileSize; i++) {
            fputc('A', sourceFile); //overwriting file with contents of A until it getss to the specific file size
        }

        fclose(sourceFile);//close file

        clock_t startTime = clock();//clock time declaration

        FILE *destFile = fopen(destFilename, "wb");//open destination file
        if (destFile == NULL) {
            perror("Failed to open destination file");//error handle
            return EXIT_FAILURE;//teriminate with error
        }

        char *buffer = (char *)malloc(chunkSize);//buffer to the value of the user set chunksize for byte-byte or chunk-chunk analysis
        if (buffer == NULL) {
            perror("Failed to allocate memory for the buffer");//error handle
            return EXIT_FAILURE;//terminate with error
        }

        size_t bytesRead, bytesWritten; //declaration

        while ((bytesRead = fread(buffer, 1, chunkSize, sourceFile)) > 0) {
            bytesWritten = fwrite(buffer, 1, bytesRead, destFile);
            if (bytesWritten != bytesRead) {
                perror("Write error");//write error
                fclose(sourceFile);//close source file
                fclose(destFile);//close destination file
                free(buffer);//free buffer mem
                return EXIT_FAILURE;//terminate with error
            }
        }

        fclose(destFile);//close destination file
        free(buffer);//free buffer mem

        clock_t endTime = clock(); //time declaration

        double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;//elapsed time by subtracting start/end times
        results[resultIndex] = elapsedTime;//results

        printf("Test %lu MB (Chunk Size: %lu bytes): %.6f seconds\n", fileSize / FILESIZE1MB, chunkSize, elapsedTime); //test

        resultIndex++;//increment
    }

    free(results);//free mem

    return 0;
}
