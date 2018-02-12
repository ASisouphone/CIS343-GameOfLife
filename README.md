# CIS343-GameOfLife

A simulation of Comway's Game of Life. Uses dyanmically sized arrays to simulate a universe of cells interacting with one another based on a certain set of rules. The purpose of this project is to gain proficiency with memory management of multi-dimensional arrays.

Notes:
- The program can load text files from the command line. If a file is not entered, the default testfile.txt will load in.
- The default testfile.txt is a 5x5 world with one Blinker oscilator.
- The text files cannot make a board larger than 9x9 because of how the program reads single characters from the buffer.
- This was coded with Atom and compiled with clang GameOfLife.c file_utilities.c and ran using ./a.out <filename>
