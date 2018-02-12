#include "file_utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
 * A simulation of Comway's Game of Life. Uses dyanmically sized arrays to
 * simulate the a universe of cells interacting with one another based on a
 * certain set of rules. The purpose of this project is to gain proficiency with
 * memory management of multi-dimensional arrays.
 *
 * @Author Alan Sisouphone
 * @version 2/6/18 Winter 2018
 *******************************************************************************/



/******************************************************************************
 * Reads the contents of a specified file into a buffer
 * @param world the current world array
 * @param row the number of rows in the world
 * @param col the number of colums in the world
 *******************************************************************************/
void allocateWorld(int*** world, int row, int col) {

    // Functionality sourced from:
    // https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/

    // Allocates the number of rows for the world
    (*world) = (int**)malloc(row * sizeof(int*));

    // Allocates the number of columns for the world
    for (int i = 0; i < row; i++) {
        (*world)[i] = (int*)malloc(col * sizeof(int));
    }
}


/******************************************************************************
 * Counts the number of alive cells ihe current world
 * @param world the current world array
 * @param row the number of rows in the world
 * @param col the number of colums in the world
 *******************************************************************************/
int aliveCount (int*** world, int row, int col) {

    // Keeps track of how many alive cells there are in the current world
    int count = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {

            // Increment the counter every time an alive cell is found
            if ((*world)[i][j]==1) {
                count++;
            }
        }
    }
    return count;
}


/******************************************************************************
 * Saves the current world data as a textfile
 * @param world the current world array
 * @param row the number of rows in the world
 * @param col the number of colums in the world
 * @param filename name of the file to be saved to
 * @return -1 is returned for errors and 1 for saving sucessfully
 *******************************************************************************/
int saveWorld(int*** world, int row, int col, char* filename) {

    // Creates the buffer to get data from the current world
    char* buffer;

    // Ensures iterations start after the first 3 indexes
    int bIndex = 3;

    // Counts number of alive cells and creates enough space to store all
    // neccessary world data. Each point in the world needs 3 indexes
    int aliveCells = (aliveCount(&(*world), row, col) * 3) + 3;

    // Allocates memory for buffer based on number of alive cells in world
    buffer = (char*)malloc(aliveCells*sizeof(char));

    // Makes the first 3 indexes of buffer store row and column width of world
    buffer[0] = row + '0';
    buffer[1] = col + '0';
    buffer[2] = '\n';

    // Adds the locations of the alive cells in the world
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if ((*world)[i][j] == 1) {

                // Makes the integers compatible with the char array buffer
                buffer[bIndex] = i + '0';
                buffer[bIndex+1] = j + '0';
                buffer[bIndex+2] = '\n';
                bIndex += 3;
            }
        }
    }

    // Writes the data from buffer into a specified textfile
    int errorCode = write_file( filename, buffer, aliveCells);

    // Frees the memory allocated by buffer since it is no longer needed
    free(buffer);

    // Error code is returned for debugging purposes
    return errorCode;
}


/******************************************************************************
 * Loads world data from a textfile into the current world
 * @param world the current world array
 * @param row the number of rows in the world
 * @param col the number of colums in the world
 * @param filename name of the file to be loaded from
 * @return -1 is returned for errors and fileSize for loading successfully
 *******************************************************************************/
int loadWorld(int*** world, int* row, int* col, char* filename) {

    // Creates buffer to gather world data from file
    char* buffer;

    // Store file size while also reading from file
    int fileSize = read_file(filename, &buffer);

    // Error if the fileSize is returned as -1
    if (fileSize == -1) {
        return -1;
    }

    // Row and column lengths are defined by the first two entries of the file
    *row = buffer[0] - '0';
    *col = buffer[1] - '0';

    // Allocates appropriate memory based on row and column length
    allocateWorld(&(*world), *row, *col);

    // Initializes each cell to be zero or 'dead'
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            (*world)[i][j] = 0;
        }
    }

    // Create local iter variables for the row and columns in order to assign
    // specific locations in the world to have alive cells
    int tempI;
    int tempJ;

    // Starts at 3 because the first 3 rows were read earlier
    for (int i = 3; i<fileSize; i++) {

        // Adds alive cells to their respective locations.
        // Also converts char to integer for i & j
        tempI = buffer[i] - '0';
        tempJ = buffer[i+1] - '0';
        (*world)[tempI][tempJ] = 1;

        // Skip through iteration because locations were already accessed
        i += 2;
    }

    // free buffer because it has served its purpose
    free(buffer);
    return fileSize;
}


/******************************************************************************
 * Prints the current world information in a formatted manner
 * @param world the current world array
 * @param row the number of rows in the world
 * @param col the number of colums in the world
 *******************************************************************************/
void printWorld(int*** world, int row, int col) {

    for (int i = 0; i < row; i++) {
        printf("\n");
        for (int j = 0; j < col; j++) {

            // Prints the data of the world
            printf("%d ", (*world)[i][j]);
        }
    }
    printf("\n\n");
}


/******************************************************************************
 * Prints the current world information in a formatted manner
 * @param world the current world array
 * @param r the current row value being evaluated (i)
 * @param c the current column value being evaluated (j)
 * @param row the number of rows in the world
 * @param col the number of columns in the world
 * @return the count of all the neighboring cells
 *******************************************************************************/
int neighborCount(int*** world, int r, int c, int row, int col) {

    int count = 0;

    // These variables will vary from +1 or -1 to ensure we are accessing
    // locations within the bounds of the world
    int initialI = r;
    int initialJ = c;
    int finalI = r;
    int finalJ = c;

    // Properly sets the bounds within the world. This allows for no invalid inputs
    if (initialI - 1 >= 0) {
        initialI--;
    }
    if (initialJ - 1 >= 0) {
        initialJ--;
    }
    if (finalI + 1 < row) {
        finalI++;
    }
    if (finalJ + 1 < col) {
        finalJ++;
    }

    // Evalutes all surrounding neighbors and counts the alive cells
    for (int i = initialI; i <= finalI; i++) {
        for (int j = initialJ; j <= finalJ; j++) {

            // Doesn't count itself as a neighbor
            if ((*world)[i][j] > 0 && (i != r || j != c)) {
                count++;
            }
        }
    }
    return count;
}


/******************************************************************************
 * Enforces the rules for each individual cell based on the current state of
 * the world. This method is necessary so we don't need to make a copy of the
 * current world
 * @param world the current world array
 * @param row the number of rows in the world
 * @param col the number of colums in the world
 *******************************************************************************/
void checkRules(int*** world, int row, int col) {

    // Checks to see if each cell in the world abides by the rules
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {

            // An alive cell with less than two neighbors dies
            if (((*world)[i][j]== 1)  && (neighborCount(&(*world),i,j,row,col) < 2)) {

                // Value of 2 means a cell that needs to be changed to dead
                (*world)[i][j] = 2;
            }

            // An alive cell with more than three neighbors dies
            else if ((*world)[i][j]== 1 && (neighborCount(&(*world),i,j,row,col) > 3)) {
                (*world)[i][j] = 2;

            }

            // A dead  cell with exactly 3 neighbors comes to life
            else if ((*world)[i][j]== 0 && (neighborCount(&(*world),i,j,row,col) == 3)) {

                // Value of -1 means a cell that needs to be changed from dead to alive
                (*world)[i][j] = -1;

            }
        }
    }
}

/******************************************************************************
 * Updates the world information of alive and dead cells based on previous
 * changes made by the enforeRules() function
 * @param world the current world array
 * @param row the number of rows in the world
 * @param col the number of colums in the world
 *******************************************************************************/
void updateWorld(int*** world, int row, int col) {

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {

            // Any cells labeled as a two will be set as dead
            if ((*world)[i][j]== 2) {
                (*world)[i][j] = 0;
            }
            else if ((*world)[i][j] == -1) {

                // Cells labeled as -1 will be set as alive
                (*world)[i][j] = 1;
            }
        }
    }
}

/******************************************************************************
 * Frees any the memory allocated by the 2D world array
 * @param world the current world array
 * @param row the number of rows in the world
 *******************************************************************************/
void freeMemory(int*** world, int row) {

    // Frees memory for the pointers within the array
    for (int i = 0; i < row; i++) {
        free((*world)[i]);
    }

    // Frees the memory for the overall array
    free((*world));
}


/******************************************************************************
 * Brings all the functions together to run the Game of Life. Also manipulates
 * terminal inputs and outputs for a makeshift user interace
 * @param argc the number of inputs from command-line
 * @param argv an array of the inputs from command-line
 * return any integer to end the program
 *******************************************************************************/
int main(int argc, char** argv){

  // The row and column width of the world
  int row,col;

  // 2D dynamic array for the world
  int** world;

  // The current generation of the world
  int generation = 0;

  // Keeps the default file to load from
  char* defaultFile = "testfile.txt";


    // Checks if the user entered a file to load from
    if (argv[1] != NULL) {

        // Loads default file if there is an error
        if ((loadWorld(&world, &row, &col, argv[1])) == -1) {
            printf("File was not found. Loading default %s instead...\n", defaultFile);
            loadWorld(&world, &row, &col, "testfile.txt");
        }

        // Otherwise the file loaded successfully
        else {
            printf("File successfully loaded");
        }
    }
    else {

        // Loads the default file if no file is specified
        printf("Load file was not specified.\n");
        printf("Loading default load file %s instead...\n", defaultFile);

        // Loads default file into the world
        loadWorld(&world, &row, &col, "testfile.txt");
    }

    do {

        // Set default values for the input commands and parameters
        char command[20] = "none";
        char parameter[20] = "none";

        // Prints off the current generation for the world
        printf("\nGeneration: %d\n", generation);

        // Prints entire world
        printWorld(&world, row, col);

        // Instructions for the game
        printf("Please enter one of the following commands as shown:\n");
        printf("Save <filename>\n");
        printf("Load <filename>\n");
        printf("Continue (or just enter 'C')\n");
        printf("Iterate <Number of Iterations>\n");
        printf("Exit\n\n");
        printf("Input: ");

        // Holds the input of the user
        char input[128];

        // Puts input into variable
        fgets(input, sizeof(input), stdin);

        // Takes the user input into a command and parameter
        sscanf(input, "%s %s", command, parameter);

        // Checks what command the user inputted and whether if it has a parameter
        // Checks for the 'Save' command and its paramter
        if (strcmp(command, "Save") == 0 && strcmp(parameter, "none") != 0) {
            if ((saveWorld(&world, row, col, parameter)) == -1) {
                printf("The file was not saved correctly\n");
            }
            else {
                printf("The file saved successfully");
            }

        }

        // Checks for the 'Load' command and its parameter
        else if (strcmp(command, "Load") == 0 && strcmp(parameter, "none") != 0) {
            if (loadWorld(&world, &row, &col, parameter)==-1) {
                printf("The file %s was not found or could not be loaded\n", parameter);
            }
            else {
                printf("File was successfully loaded");
                generation = 0;
            }

        }

        // Checks for the 'Continue' or 'C' command only
        else if (strcmp(command, "Continue") == 0 || command[0] == 'C') {
            checkRules(&world, row, col);
            updateWorld(&world, row, col);
            generation++;
        }

        // Checks for the 'iterate' command and its paramter
        else if (strcmp(command, "Iterate") == 0 && strcmp(parameter, "none") != 0) {
            int iterNum = 0;

            sscanf(parameter, "%d", &iterNum);

            for (int i = 0; i < iterNum; i++) {
                checkRules(&world, row, col);
                updateWorld(&world, row, col);
                generation++;
            }
        }

        // Checks for the 'Exit' command only
        else if (strcmp(command, "Exit") == 0) {

            // Free memory before the program terminates
            freeMemory(&world, row);

            // This terminates the program
            return 0;

        }
        else {

            // Commands that don't match the specified checks are not valid
            printf("The command was not valid\n");
        }

    }

    // Continue doing this until the program is exited.
    while (1);
    return 0;
}
