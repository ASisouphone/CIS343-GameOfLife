#include "file_utilities.h"

#include <stdio.h>
#include <stdlib.h>

// https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/

void allocateWorld(int*** world, int row, int col) {
  (*world) = (int**)malloc(row * sizeof(int*));
  for (int i = 0; i < row; i++) {
    (*world)[i] = (int*)malloc(col * sizeof(int));
  }
}

void createWorld(int*** world, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      (*world)[i][j] = 0;
    }
  }
}


void checkRules(int*** world,int i, int j) {
  if ((*world)[i][j] == 0) {
    (*world)[i][j] = 1;
  }
}

  void printWorld(int*** world, int row, int col) {

    for (int i = 0; i < row; i++) {
        printf("\n");
      for (int j = 0; j < col; j++) {
        printf("%d ", (*world)[i][j]);
      }
    }
    printf("\n");

  }


  void freeMemory(int*** world, int row) {
    for (int i = 0; i < row; i++) {
      free((*world)[i]);
    }
    free(*world);
  }

//    int neighborCount(int ** world, int, int j) {
//        int count = 0;


//        [1][1]
//
//        We need to check:
//        [0][0], [0][1], [0][2],
//        [1][0],       , [1][2]
//        [2][0], [2][1], [2][2]
//
//        We do not want negatives or anything > R and C




int main(int argc, char** argv){
    printf("Howdy all!\n\n");
    printf("This program was provided with %d command-line arguments.\n\n", argc);
    printf("These arguments are:\n====================\n\n");
    for(int i=0; i<argc; i++){
        printf("\t%s\n", argv[i]);
    }

    int row,col;
    row = atoi(argv[1]);
    col = atoi(argv[2]);

    printf ("%d\n", row);
    printf ("%d\n", col);

    int** world;

    allocateWorld(&world, row, col);

    createWorld(&world, row, col);

    printWorld(&world, row, col);

    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        checkRules(&world,i,j);
      }
    }

    printWorld(&world, row, col);

    freeMemory(&world, row);

    return 0;
}
