#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utilities.h"
/*
 * file_utilities.c saves and loads from txt file.
 * Save increments through the 2D array, using periods to
 * denote the end of a row.
 * Load then parses a string of integers,
 * where row = the number of periods, and col = the number
 * of integers before the first period.
 *
 */
//#include <file_utilities.h>
/*
 * Don't have to use user input, could just load from a file.
 * char **arr... address to an array? Or 2D array?
 * *arr[11];
 * Board =  one long array that 'wraps'.
 * OR, actual 2D array. - easier to use. char ** arr.
 * malloc(int*)
 * for (numRows)
 *     arr[i] = (int*)malloc // num of columns
 *
 * Don't forget to free memory at the end. Inner first, then big.
 *
 * Read and write? create libraries... Could even use them later by linking .o file.
 *
 * Tentative Monday date.
 */

/*  https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/  */
/*  https://stackoverflow.com/questions/18688971/c-char-array-initialization  */

void createBoard(int r, int c);
void printBoard(int r, int c);
void loadBoard();
int saveBoard();
void updateBoard(int n);
int promptUser();
int freeBoard();

int row = 0;
int col = 0;
int generations;
char usrIn[10];
/*
 * Using board, determine the next game state onto board2, then overwrite
 * board with tempBoard.
 */
char **board; // 2D array
//char *fileName;
char fileName[30];

/*
 * TODO: Get rid of as many global variables as possible.
 * TODO: Toggle option for showing prompt text?
 */
int main(int argc, char const *argv[]) {
    /*
    if (argc != 2) {
        printf("Usage: Number_of_rows Number_of_columns\n");
        exit(1);
    }
    */
    if (argc == 2) {
        row = atoi(argv[1]);
        col = atoi(argv[2]);
    }

    while (1) {
        //fflush(stdin);
        switch (promptUser()) {
            case 1: // Update 1 generation
                updateBoard(1);
                break;
            case 2: // Update n generations
                printf("Number of generations: \n");
                fflush(stdin);
                fgets(usrIn, sizeof(usrIn), stdin);
                generations = atoi(usrIn);
                updateBoard(generations);
                break;
            case 3: // Save
                //memset(fileName, 0, strlen(fileName)); // zeros out array
                printf("Save as?: (All files currently route to 'state.txt', "
                               "any input will do.)\n");
                fflush(stdin);
                fgets(fileName, 31, stdin);
                saveBoard();
                break;
            case 4: // Load
                //memset(fileName, 0, strlen(fileName)); // zeros out array
                //fileName = (char*)malloc(30 * sizeof(char));
                printf("Load file name: (All files currently route to 'state.txt', "
                               "any input will do.)\n");
                fflush(stdin);
                fgets(fileName, 31, stdin);
                loadBoard();
                break;
            case 5: // Exit
                printf("Destroying world. How can you sleep at night? \n");
                freeBoard();
                exit(0);
            case 6:
                //printBoard();
                break;
            default:
                break;
        }
    }
}

/*
 *  Any live cell with fewer than two neighbors dies (underpopulation)
    Any live cell with more than three neighbors dies (overcrowding)
    Any live cell with two or more live neighbors lives another generation
    Any dead cell with exactly three live neighbors become a live cell
 */
void updateBoard(int n) {
    char **tempBoard;
    int i = 0;
    for (i; i < n; i++) {

    }
    printBoard(row, col);
}

int promptUser() {
    int selection = 0;
    char c[2];

    printf("What would you like to do?\n");
    printf("(1) Generate\n");
    printf("(2) Generate __# of times\n");
    printf("(3) Save\n");
    printf("(4) Load\n");
    printf("(5) Quit\n");
    //printf("(5) Spawn life at coordinates: X Y\n");

    fflush(stdin); // Clears troublesome '\n' character left in console.
    fgets(c, 2, stdin);
    selection = atoi(c); //strtol?
    return selection;
}

void printBoard(int r, int c) {
    row = r;
    col = c;
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int saveBoard() {
    int i, j = 0;
    int size = 0;
    char *str;
    str = (char*)malloc((row * (col + 1)) * sizeof(char));
    if (board == NULL) {
        printf("There's no board to save.\n");
        return 1;
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {

            str[size] = board[i][j];
            size++;
        }
        str[size] = '.';
        size++;
    }
    write_file(fileName, str, size);
    printf("Game saved.\n");
}

/*
 * Number of periods = row size
 * Characters before a period = col size
 * read_file assigns one long string to str,
 * we must then take this string and used periods to
 * determine row & col, and then fill in the game board.
 */
void loadBoard() {
    char *str;
    int size;
    if ((size = read_file(fileName, &str)) > 1) {
        // Board now contains periods, which will be used
        // to determine row ends, and must then be removed.
        row = 0;
        col = 0;
        int i, j = 0;

        // Get row size
        while (str[col] != '.') {
            col++;
        }
        for (i = 0; i < size; i++) {
            if (str[i] == '.') {
                row++;
            }
        }

        freeBoard(); // Clear out previous board, if it exists
        createBoard(row, col);
        /* Fill the board. Since row and col are accurate to the
         * board size, but we are iterating through a string that still
         * contains periods to denote the end of rows, then we must
         * add one to col in the loop to account for each extra char.
         */
        int n = 0;
        for (i = 0; i < row; i++) {
            for (j = 0; j < col + 1; j++) {
                if (str[n] != '.') {
                    board[i][j] = str[n];
                }
                n++;
            }
        }
        printBoard(row, col);
    }
    free(str);
}

/*Board is the address to an array of addresses,
 * each of which is an address to the first element
 * of an array.
 */
void createBoard(const int r, const int c) {
    int i, j;
    row = r;
    col = c;
    board = (char **)malloc(row * sizeof(char*));
    for (i = 0; i < row; i++) {
        board[i] = (char*)malloc(col * sizeof(char));
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            board[i][j] = '-';
        }
    }
}

int freeBoard() {
    int i;
    if (board != NULL) {
        for (i = 0; i < row; i++) {
            free(board[i]);
        }
        free(board);
    }
}