#include <stdlib.h>
#include <stdio.h>
#include <io.h>

// Created by Sean Aubrey on 2/9/2018.

/* file_utilities.c saves and loads from txt file.
 * Readfile returns the size of the array read in if successful,
 * otherwise 1. Buffer is a ptr to an array, not a 2D array.
 *
 * Both currently only use a preset file name.
 */
int read_file(char *filename, char **buffer ) {
    FILE *fin;
    filename = "state.txt";
    fin = fopen(filename, "r");

    int size = 0;
    // Iterate through buffer to determine row/col sizes.
    if (filename == NULL || fin == NULL) {
        printf("File does not exist!\n");
        fclose(fin);
        return 1;

    } else {
        fseek(fin, 0L, SEEK_END); // move to end
        size = (int)ftell(fin); // get size of file
        if (size <= 1) {
            printf("Nothing in file. \n");
            fclose(fin);
            return 1;
        }

        *buffer = (char*)malloc(size * sizeof(char));
        fseek(fin, 0L, SEEK_SET); // Return fin to start.
        fread(*buffer, sizeof(char), size, fin);

        fclose(fin);
        return size;
    }
}

/*
 * If we have the size, which is row * col, then we can read the first row
 * and determine the number of columns. col = size/row
 * These are generic functions that can be used to read/write any array.
 * Row/col handling must occur in main.
 */
int write_file(const char* filename, char *buffer, int size) {
    FILE *fout;
    //fout = fopen(filename, "w");
    fout = fopen("state.txt", "w");

    if (filename == NULL || fout == NULL) {
        printf("Not a valid file name!\n");
        fclose(fout);
        return 1;
    }

    int i;
    for (i = 0; i < size; i++) {
        fputc(buffer[i], fout);
    }
    fclose(fout);
    return 0;
}