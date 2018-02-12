#include "file_utilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/

void allocateWorld(int*** world, int row, int col) {
  (*world) = (int**)malloc(row * sizeof(int*));
  for (int i = 0; i < row; i++) {
    (*world)[i] = (int*)malloc(col * sizeof(int));
  }
}

void resetWorld(int*** world, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      (*world)[i][j] = 0;
    }
  }
}


  int aliveCount (int*** world, int row, int col) {
    int count = 0;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if ((*world)[i][j]==1) {
          count++;
        }
      }
    }
    return count;
  }

  int saveWorld(int*** world, int row, int col, char* filename) {

    //printf("%s\n", "During saveWorld");


    char* buffer;

    int bIndex = 3;

    //printf("%s\n", "During saveWorld 2");


    int aliveCells = (aliveCount(&(*world), row, col) * 3) + 3;

    //printf("Alive:%d\n", aliveCells);

    buffer = (char*)malloc(aliveCells*sizeof(char));

    buffer[0] = row + '0';
    buffer[1] = col + '0';
    buffer[2] = '\n';

    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if ((*world)[i][j] == 1) {
          buffer[bIndex] = i + '0';
          buffer[bIndex+1] = j + '0';
          buffer[bIndex+2] = '\n';
          bIndex += 3;
          //printf("%d\n", bIndex);
        }
      }
    }

    int errorCode = write_file( filename, buffer, aliveCells);


    free(buffer);
    //printf("%s\n", buffer);
    return errorCode;

  }



  int loadWorld(int*** world, int* row, int* col, char* filename) {



    // *row = 5;
    // *col = 5;

    char* buffer;
//
    int fileSize =   read_file(filename, &buffer);

    if (fileSize == -1) {
      return -1;
    }
    // *row = atoi(*buffer[0]);
    // *col = atoi(*buffer[1]);

    // for (int i = 0; i <= fileSize; i++) {
    //   printf("%c ", buffer[i]);
    // }

    for (int i = 0; i<=fileSize; i++) {
      //printf("Read From File: %d\n", buffer[i]);
    }

    *row = buffer[0] - '0';
    *col = buffer[1] - '0';

    allocateWorld(&(*world), *row, *col);
    //
    for (int i = 0; i < *row; i++) {
      for (int j = 0; j < *col; j++) {
        (*world)[i][j] = 0;
      }
    }

    for (int i = 0; i<=fileSize; i++) {
      if (buffer[i]=='\n') {
        //printf("%s\n", "OMG IT's NEWLINE CHARACTER");
      }
      //printf("%i: %c\n", i, buffer[i]);
    }



    int tempI;
    int tempJ;
    for (int i = 3; i<fileSize; i++) {
      tempI = buffer[i] - '0';
      tempJ = buffer[i+1] - '0';
      //printf("I: %d (%d,%d)", i, tempI, tempJ);

      (*world)[tempI][tempJ] = 1;
      i += 2;
    }

    free(buffer);
    return fileSize;

}



// bool isAlive(int*** world, int i, int j) {
//   if ((*world)[i][j] == 1) {
//     return true;
//   }
//   return false;
// }

  void printWorld(int*** world, int row, int col) {

    for (int i = 0; i < row; i++) {
        printf("\n");
      for (int j = 0; j < col; j++) {
        printf("%d ", (*world)[i][j]);
      }
    }
    printf("\n\n");

  }


  void freeMemory(int*** world, int row) {
    for (int i = 0; i < row; i++) {
      free((*world)[i]);
    }
    free((*world));
  }

   int neighborCount(int*** world, int r, int c, int row, int col) {
       int count = 0;

       int initialI = r;
       int initialJ = c;

       int finalI = r;
       int finalJ = c;

       // Properly sets the bounds within the board
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


      //  printf("(%d,%d) to (%d,%d) ", initialI, initialJ, finalI, finalJ );

       for (int i = initialI; i <= finalI; i++) {
         for (int j = initialJ; j <= finalJ; j++) {
           if ((*world)[i][j] > 0 && (i != r || j != c)) {
               count++;
              //  printf("THIS(%d,%d)", i,j);
           }
         }
       }
      return count;
    }


    void checkRules(int*** world, int row, int col) {
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          if (((*world)[i][j]== 1)  && (neighborCount(&(*world),i,j,row,col) < 2)) {
            (*world)[i][j] = 2;
          }
          else if ((*world)[i][j]== 1 && (neighborCount(&(*world),i,j,row,col) > 3)) {
            (*world)[i][j] = 2;

          }
          // else if ((*world)[i][j]== 1 && (neighborCount(&(*world),i,j,row,col) >= 2)) {
          //   (*world)[i][j] = 0;
          //
          // }
          else if ((*world)[i][j]== 0 && (neighborCount(&(*world),i,j,row,col) == 3)) {
            (*world)[i][j] = -1;

          }
        }
      }
    }

    void updateWorld(int*** world, int row, int col) {
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
          if ((*world)[i][j]== 2) {
            (*world)[i][j] = 0;
          }
          else if ((*world)[i][j] == -1) {
            (*world)[i][j] = 1;
           }
        }
      }
    }



    void printNeighbors(int*** world, int row, int col) {
      for (int i = 0; i < row; i++) {
        printf("\n");
        for (int j = 0; j < col; j++) {
          //checkRules(&world,i,j);
          printf("%d ", neighborCount(&(*world), i, j, row, col));
          // neighborCount(&world, i, j, row, col);
        }
      }
      printf("\n");
    }



int main(int argc, char** argv){
    // printf("Howdy all!\n\n");
    // printf("This program was provided with %d command-line arguments.\n\n", argc);
    // printf("These arguments are:\n====================\n\n");
    // for(int i=0; i<argc; i++){
    //     printf("\t%s\n", argv[i]);
    // }

    int row,col;
    int** world;
    int generation = 0;

    char* defaultFile = "testfile.txt";


    // Checks if the user entered a file to load from
    if (argv[1] != NULL) {
      // Loads the file the user entered
      if ((loadWorld(&world, &row, &col, argv[1])) == -1) {
        printf("File was not found. Loading default %s instead...\n", defaultFile);
        loadWorld(&world, &row, &col, "testfile.txt");
      }
      else {
        printf("File successfully loaded");
      }
    }
    else {
      // Loads the default file if no file is specified
      printf("Load file was not specified.\n");
      printf("Loading default load file %s instead...\n", defaultFile);

      loadWorld(&world, &row, &col, "testfile.txt");
    }

    do {
      int result;
      char command[20] = "none";
      char parameter[20] = "none";

      printf("\nGeneration: %d\n", generation);
      printWorld(&world, row, col);

      printf("Please enter one of the following commands as shown:\n");
      printf("Save <filename>\n");
      printf("Load <filename>\n");
      printf("Continue (or just enter 'C')\n");
      printf("Iterate <Number of Iterations>\n");
      printf("Exit\n\n");
      printf("Input: ");

      char input[1024];
      fgets(input, sizeof(input), stdin);
      sscanf(input, "%s %s", command, parameter);


        if (strcmp(command, "Save") == 0 && strcmp(parameter, "none") != 0) {
          if ((saveWorld(&world, row, col, parameter)) == -1) {
            printf("The file was not saved correctly\n");
          }
          else {
            printf("The file saved successfully");
          }

        }
        else if (strcmp(command, "Load") == 0 && strcmp(parameter, "none") != 0) {
          if (loadWorld(&world, &row, &col, parameter)==-1) {
            printf("The file %s was not found or could not be loaded\n", parameter);
          }
          else {
            printf("File was successfully loaded");
            generation = 0;
          }

        }
        else if (strcmp(command, "Continue") == 0 || command[0] == 'C') {
          checkRules(&world, row, col);
          updateWorld(&world, row, col);
          generation++;
        }
        else if (strcmp(command, "Iterate") == 0 && strcmp(parameter, "none") != 0) {
          int iterNum = 0;

          sscanf(parameter, "%d", &iterNum);

          for (int i = 0; i < iterNum; i++) {
            checkRules(&world, row, col);
            updateWorld(&world, row, col);
            generation++;
          }
        }
        else if (strcmp(command, "Exit") == 0) {

          freeMemory(&world, row);
          return 0;

        }
        else {
          printf("The command was not valid\n");
        }

      }

    while (1);


    return 0;



    // int row,col;
    // row = atoi(argv[1]);
    // col = atoi(argv[2]);
    //
    // printf ("%d\n", row);
    // printf ("%d\n", col);


    // char* buffer;
    //
    // int fileSize =   read_file("testfile.txt", &buffer);
    //
    // for (int i = 0; i<=fileSize; i++) {
    //   printf("%c\n", buffer[i]);
    // }


    //loadWorld(&world, &row, &col);

    printf("%d,%d TESTING ", row, col);


    //allocateWorld(&world, row, col);

    //resetWorld(&world, row, col);

    printWorld(&world, row, col);

    // printf("\n%d\n", neighborCount(&world, 0,0,row,col));
    // printNeighbors(&world, row, col);
    checkRules(&world, row, col);
    updateWorld(&world, row, col);
    printWorld(&world, row, col);

    checkRules(&world, row, col);
    // printWorld(&world, row, col);
    updateWorld(&world, row, col);
    printWorld(&world, row, col);


    checkRules(&world, row, col);
    updateWorld(&world, row, col);
    printWorld(&world, row, col);


    checkRules(&world, row, col);
    updateWorld(&world, row, col);
    printWorld(&world, row, col);

printf("%d\n", aliveCount(&world, row, col));
    printf("%s\n", "Before saveWorld");

    printf("%d\n", aliveCount(&world, row, col));

   saveWorld(&world, row, col, "test");



    // printWorld(&world, row, col);


    return 0;
}
