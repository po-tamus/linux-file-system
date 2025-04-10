// C program to Open a File,
// Write in it, And Close the File
#include <stdio.h>
#include <string.h>

int reader() {
    FILE *fp; 
    fp = fopen("test-file.txt", "r");
    char dataBuffer[256];

    fp = fopen("test-file.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return 1; 
    }

    printf("The file was opened.\n");

    while (fgets(dataBuffer, sizeof(dataBuffer), fp) != NULL) {
        printf("%s\n", dataBuffer);
    }

    fclose(fp);
    return 0;
}

/**
 * this will print 24 since there are 24 bytes in test-file.txt
 */
int seeker() {
    FILE* fp;
    fp = fopen("test-file.txt", "r");

    // Moving pointer to end
    fseek(fp, 0, SEEK_END);

    // Printing position of pointer
    printf("%ld \n", ftell(fp));

    return 0;
}

/**
 * This will write to a file
 * If it doesn't exist, the file will be created since we are
 * opening it with the "w" flag
 */
int writer() {

    // Declare the file pointer
    FILE* filePointer;

    // Get the data to be written in file
    char dataToBeWritten[50] = "GeeksforGeeks-A Computer "
                               "Science Portal for Geeks";

    // Open the existing file GfgTest.c using fopen()
    // in write mode using "w" attribute
    // this will create it if it doesn't exist
    filePointer = fopen("GfgTest.txt", "w");

    // Check if this filePointer is null
    // which maybe if the file does not exist
    if (filePointer == NULL) {
        printf("GfgTest.txt file failed to open.");
    }
    else {

        printf("The file is now opened.\n");

        // Write the dataToBeWritten into the file
        if (strlen(dataToBeWritten) > 0) {

            // writing in the file using fputs()
            fputs(dataToBeWritten, filePointer);
            fputs("\n", filePointer);
        }

        // Closing the file using fclose()
        fclose(filePointer);

        printf("Data successfully written in file "
               "GfgTest.txt\n");
        printf("The file is now closed.\n");
    }
  
    return 0;
}

int main() {
    reader();
    printf("\n");
    writer();
    printf("\n");
    seeker();
    return 0; 
}