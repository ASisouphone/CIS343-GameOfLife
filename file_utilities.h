//
//  Created by Alan Sisouphone 2/6/18
//

#ifndef _H_FILE_UTILITIES_
#define _H_FILE_UTILITIES_

/******************************************************************************
 * Reads the contents of a specified file into a buffer
 * @param filename name of the file to read
 * @param buffer contains data read from file
 * @return returns the file size on success or -1 for errors
 *******************************************************************************/
int read_file( char* filename, char **buffer );

/******************************************************************************
 * Writes data to a specified file
 * @param filename name of the file to written to
 * @param buffer contains the data to write from
 * @param size contains the size of the file to be written to
 * @return returns the 1 on success and -1 for errors
 *******************************************************************************/
int write_file( char* filename, char *buffer, int size);

#endif
