// C program to write to a Binary file using fwrite()
#include <stdio.h>
#include <stdlib.h>

#define NUM_PIXELS 10

struct pixel {
  char red, green, blue; 
};

int main () {
  int n;
  // Structure variable declared here.
  struct pixel pix;
  FILE* fptr;

  // write to a binary file 
  if ((fptr = fopen("image.dat", "wb")) == NULL) {
    printf("Error opening file");
    exit(1);
  }

  int flag = 0;
  // write out the number of pixels 
  for (n = 1; n < NUM_PIXELS; n++) {
    pix.red = n;
    pix.green = 5 * n;
    pix.blue = 1<< (n%6) ;

    // write out a single pixel
    flag = fwrite(&pix, sizeof(struct pixel), 1 , fptr);

    if (!flag) {
      printf("Write Failed \n");
      exit(1); 
    }
    
  }

  // close the file 
  fclose(fptr);
  
  return 0;
}


