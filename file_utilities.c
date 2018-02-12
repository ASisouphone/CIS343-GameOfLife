#include "file_utilities.h"

#include <stdio.h>
#include <stdlib.h>

//http://www.fundza.com/c4serious/fileIO_reading_all/index.html

int read_file( char* filename, char **buffer ) {
  FILE* file;
  int fileSize;

  file = fopen(filename, "r");

  if (file == NULL) {
    return -1;
  }

  fseek(file, 0L, SEEK_END);
  fileSize = ftell(file);

  fseek(file, 0L, SEEK_SET);

  //printf("FileSize: %d\n", fileSize);

  *buffer = (char*)malloc(fileSize);
  // *buffer = (char*)calloc(fileSize, sizeof(char));

  if (*buffer == NULL) {
    return -1;
  }

  fread(*buffer, sizeof(char), fileSize, file);
  fclose(file);

  //printf("The file called test.dat contains this text\n\n%s", *buffer);



  return fileSize;


}

// https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
int write_file( char* filename, char *buffer, int size) {

  FILE *file;

  if (buffer[0]== '\0') {
    return -1;
  }

  file = fopen(filename, "w");

  fwrite(buffer, sizeof(char), size, file);

  fclose(file);

  return 1;
}
