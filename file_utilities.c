#include <stdlib.h>
#include <stdio.h>
#include <io.h>
//#include <file_utilities.h>
//
// Created by Sean Aubrey on 2/9/2018.
//

/*
 * file_utilities.c saves and loads from txt file.
 * Save increments through the 2D array, using periods to
 * denote the end of a row.
 * Load then parses a string of integers,
 * where row = the number of periods, and col = the number
 * of integers before the first period.
 *
 */
int read_file( char* filename, char **buffer ) {
    FILE *fin;
    fin = open(filename, "r");
    int row, col;


    if (filename == NULL) {
        printf("File does not exist!\n");
    }

    // Read from file
    while (!feof(fin)) {


    }

    // Insert into board
    int i, j;
    for (i = 0; i < row; row++) {
        for (j = 0; j < col; col++) {

        }
    }
}
int write_file( char* filename, char *buffer, int size) {
    FILE *fout;
    fout = open(filename, "w");



}