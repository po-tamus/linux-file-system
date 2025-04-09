/* example using the C standard library 
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[256]; // Adjust buffer size as needed
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    if (ferror(file)) {
      perror("Error reading file");
      fclose(file);
      return 1;
    }

    fclose(file);
    return 0;
}
