//
//  Created by Alan Sisouphone on 2/6/18
//

#include "file_utilities.h"
#include <stdio.h>
#include <stdlib.h>

int read_file( char* filename, char **buffer ) {

  // Functionality is sourced from:
  // http://www.fundza.com/c4serious/fileIO_reading_all/index.html

  // Holds a pointer to a FILE struct
  FILE* file;

  // Holds the file size of the current file
  int fileSize;

  // Opens the file to be read from
  file = fopen(filename, "r");

  // Error if the file is not found
  if (file == NULL) {
    return -1;
  }

  // Finds the size in bytes of the file
  fseek(file, 0L, SEEK_END);
  fileSize = ftell(file);
  fseek(file, 0L, SEEK_SET);

  // Allocates enough memory in the buffer to hold the file contents
  *buffer = (char*)malloc(fileSize);

  // Error if the buffer is not allocated correctly
  if (*buffer == NULL) {
    return -1;
  }

  // The contents of the opened file are read into the buffer
  fread(*buffer, sizeof(char), fileSize, file);

  // Closes the current file
  fclose(file);

  return fileSize;
}


int write_file( char* filename, char *buffer, int size) {

  // Functionality is sourced from:
  // https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm

  FILE *file;

  // Error if the buffer is empty
  if (buffer[0]== '\0') {
    return -1;
  }

  // Creates a file to be written to
  file = fopen(filename, "w");

  // Writes the contents within buffer into file
  fwrite(buffer, sizeof(char), size, file);

  // Closes the current file
  fclose(file);

  return 1;
}
