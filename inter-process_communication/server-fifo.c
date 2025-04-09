// Example program to illustrate a client-server using a Unix FIFO

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 20

int main(int argc, char *argv[]) {
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    char *fifo_path;

    // Check if the FIFO path is provided as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fifo_path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    fifo_path = argv[1];

    // Create the FIFO if it doesn't exist
    // Note the FS permissions in the second argument as an octal number
    // recall setUID/owner/group/world 0666 = 0/110/110/ = -rw-rw-rw-
    if (mkfifo(fifo_path, 0666) == -1) {
        if (errno != EEXIST) {
            perror("Server: Error creating FIFO");
            exit(EXIT_FAILURE);
        }
        printf("Server: FIFO \"%s\" already exists.\n", fifo_path);
    } else {
        printf("Server: FIFO \"%s\" created successfully.\n", fifo_path);
    }

    // Open the FIFO for both reading and writing
    fd = open(fifo_path, O_RDWR);
    if (fd == -1) {
        perror("Server: Error opening FIFO for read/write");
        exit(EXIT_FAILURE);
    }
    printf("Server: Opened FIFO \"%s\" for read/write.\n", fifo_path);

    // Read from the FIFO
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1) {
        perror("Server: Error reading from FIFO");
        close(fd);
        unlink(fifo_path);
        exit(EXIT_FAILURE);
    } else if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Server: Received message: \"%s\" (%zd bytes).\n", buffer, bytes_read);

        // Echo the message back to the client
        bytes_written = write(fd, buffer, bytes_read + 1);
        if (bytes_written == -1) {
            perror("Server: Error writing back to FIFO");
        } else {
            printf("Server: Echoed message back: \"%s\" (%zd bytes).\n", buffer, bytes_written);
        }
    } else {
        printf("Server: Client closed the connection or sent no data.\n");
    }

    // Close the FIFO
    close(fd);
    printf("Server: Closed FIFO \"%s\".\n", fifo_path);

    // Clean up the FIFO
    // Unlink removes the link to the inode, if it goes to zero it is deleted 
    if (unlink(fifo_path) == -1) {
        perror("Server: Error unlinking FIFO");
    } else {
        printf("Server: FIFO \"%s\" unlinked.\n", fifo_path);
    }

    return 0;
}
