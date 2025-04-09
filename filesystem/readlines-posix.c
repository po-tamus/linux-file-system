/* example file using the posix interface 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[]) {
  int lineno;
  
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    /* note that POSIX returns and integer file descriptor */
    
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    char lineBuffer[BUFFER_SIZE * 2]; // Larger buffer for accumulating lines
    size_t lineBufferIndex = 0;

    /* read in a lineinto a buffer */
    lineno = 1; 
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the buffer
        for (ssize_t i = 0; i < bytesRead; i++) {
            lineBuffer[lineBufferIndex++] = buffer[i];
            if (buffer[i] == '\n') {
                lineBuffer[lineBufferIndex] = '\0'; // Null-terminate the line
                printf("%d %s", lineno, lineBuffer);
                lineBufferIndex = 0; // Reset for the next line
		lineno++ ; 
            }
        }
    }

    if (bytesRead == -1) {
        fprintf(stderr, "Error reading file: %s\n", strerror(errno));
        close(fd);
        return 1;
    }

    //Handle the case where the last line doesn't end with a newline.
    if(lineBufferIndex > 0){
        lineBuffer[lineBufferIndex] = '\0';
        printf("%s", lineBuffer);
    }

    close(fd);
    return 0;
}
