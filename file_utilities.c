#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Created by Sean Aubrey on 2/9/2018.

/* file_utilities.c saves and loads from txt file. */

/**
 * If the file exists, this function gets its size and
 * allocates memory accordingly under the passed in
 * pointer. It fills this memory and returns the size of
 * the array if successful, or 1 if not.
 * Buffer is a ptr to a character array, not a 2D array.
 * @param filename char* The file name destination.
 * @param buffer char** Points to the array to be filled.
 * @return size int The size of the file read.
 */
int read_file(char *filename, char **buffer ) {
    FILE *fin;
    filename[strlen(filename) - 1] = '\0';
    fin = fopen(filename, "r");

    int size = 0;
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

/**
 * Writes characters from the passed in buffer to the file,
 * for the number of characters as determined by size.
 * @param filename char* The file name destination.
 * @param buffer char* The char array to be read in.
 * @param size int The number of characters to be read in.
 * @return int 0 if successful.
 */
int write_file(char* filename, char *buffer, int size) {
    FILE *fout;
    filename[strlen(filename) - 1] = '\0';
    fout = fopen(filename, "w");

    if (fout == NULL) {
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