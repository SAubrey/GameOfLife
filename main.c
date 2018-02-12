#define LIVE 'O'
#define DEAD '-'

#include <stdio.h>
#include <stdlib.h>
#include "file_utilities.h"
/*
 * JOHN CONWAY'S GAME OF LIFE
 * Sean Aubrey
 * For CIS 343
 */
/* Some references used. */
/*
 *  https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
 *  https://stackoverflow.com/questions/18688971/c-char-array-initialization
 *  http://pubs.opengroup.org/onlinepubs/009695399/functions/fopen.html
 *  Shared ideas with Ron Rounsifer (who is in the other 343 section).
 */

void createBoard(int r, int c);
void printBoard(int r, int c);
void loadBoard();
int saveBoard();
int updateBoard(int n);
int promptUser();
void freeBoard();
int spawnCell(int x, int y);
int getCBounds(int j, int c);

int row = 0;
int col = 0;
int generations;
char gens[10];

 /* Using board, determine the next game state onto tempBoard,
  * then overwrite board with tempBoard. */
char **board; // 2D array
char **tempBoard;
char fileName[40];

/*
 * Main takes in the command line arguments
 * Number_of_rows, Number_of_columns.
 * Though they are not necessary.
 * It then enters a user input decision loop
 * that persists for the life of the program.
 */
int main(int argc, char const *argv[]) {
    printf("\n---Welcome to The Game of Life---\n\n");
    printf("Command line usage for a custom board size: \n");
    printf("Usage: Number_of_rows  Number_of_columns\n");
    printf("You can load from a text file or populate the default board. \n");
    printf("Load the default and save to see the correct text format. \n");
    printf("Replace '-' character with uppercase letter 'O'. \n\n");
    printf("What would you like to do? \n");

    if (argc == 3) {
        row = atoi(argv[1]);
        col = atoi(argv[2]);
        createBoard(row, col);
        printBoard(row, col);
    }

    int x, y;
    char ch[3];
    while (1) {
        switch (promptUser()) {
            case 1: // Update 1 generation
                updateBoard(1);
                break;
            case 2: // Update n generations
                printf("Number of generations:\n");
                fgets(gens, sizeof(gens), stdin);
                generations = atoi(gens);
                updateBoard(generations);
                break;
            case 3: // Save
                //memset(fileName, 0, strlen(fileName));
                printf("Save as?: \n");
                fgets(fileName, 40, stdin);
                saveBoard();
                break;
            case 4: // Load
                //memset(fileName, 0, strlen(fileName));
                printf("Load file name: \n");
                fgets(fileName, 40, stdin);
                loadBoard();
                break;
            case 5: // Default board
                createBoard(10, 10);
                printBoard(10, 10);
                break;
            case 6: // Spawn a cell
                x = 0;
                y = 0;
                printf("X coordinate?\n");
                fgets(ch, 3, stdin);
                x = atoi(ch);
                printf("Y coordinate?\n");
                fgets(ch, 3, stdin);
                y = atoi(ch);
                spawnCell(x, y);
                break;
            case 7: // Exit
                printf("Freeing all beings from existence.\n");
                freeBoard();
                exit(0);
            default:
                break;
        }
    }
} // end main

/**
 * This function generates the next game state based on the
 * current one. It iterates through the game board, and for
 * each element it iterates through a 3x3 grid to sum its
 * neighbors, not counting itself. The 3x3 grid must be made
 * smaller for elements on the edge of the grid. The number of
 * neighbors is then used to determine the state of the cell
 * in the next game state.
 * @param n int The number of game state generations
 * @return int 0 if successful.
 */
int updateBoard(int n) {
    int g = 0;
    int i = 0;
    int j = 0;
    if (board == NULL) {
        printf("There's no world to generate.\n");
        printf("\n");
        return 1;
    }
    /* For number of generations. */
    for (g; g < n; g++) {
        /* Clear tempBoard */
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                tempBoard[i][j] = DEAD;
            }
        }

        int r, c;
        int rcap, ccap;
        int neighbors;
        /* For each cell, count the number of live cells around it.*/
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                neighbors = 0;

                /* Create 3x3 grid bounds. */
                r = i - 1; // top bound
                rcap = i + 1; // bottom bound
                c = j - 1; // left bound
                ccap = j + 1; // right bound

                /* Determine if a row or column must be cut
                 * based on the position of the element in question.*/
                if (i == 0) {
                    r++;
                } else if (i == (row - 1)) { // account for +1 error
                    rcap--;
                }
                if (j == 0) {
                    c++;
                } else if (j == (col - 1)) {
                    ccap--;
                }

                for (r; r <= rcap; r++) {
                    /* c's orientation must be recalculated relative to
                     * the game board after incrementation. */
                    for (c = getCBounds(j,c); c <= ccap; c++) {
                        /* Don't count yourself as your neighbor. */
                        if (board[r][c] == LIVE &&
                                !((r == i) && (c == j))) {
                            neighbors++;
                        }
                    }
                }
                /* Determine fate */
                if (board[i][j] == DEAD) {
                    if (neighbors == 3) {
                        tempBoard[i][j] = LIVE;
                    }
                } else if (board[i][j] == LIVE){
                    if (neighbors < 2 || neighbors > 3) {
                        tempBoard[i][j] = DEAD;
                    } else {
                        tempBoard[i][j] = LIVE;
                    }
                }
            }
        }
        /* Copy temp to board */
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                board [i][j] = tempBoard[i][j];
            }
        }
        printBoard(row, col);
    }
    return 0;
}

/**
 * Recalculates the column to begin searching for
 * neighbors in for a specific cell.
 * @param j int of outer loop column.
 * @param c int of local loop column.
 * @return c int The re-set column number.
 */
int getCBounds(int j, int c) {
    c = j - 1; // left bound
    if (j == 0) {
        c++;
    }
    return c;
}

/**
 * Displays options, gets and returns input.
 * @return int user selection choice
 */
int promptUser() {
    int selection = 0;
    char c[3];

    //printf("What would you like to do?\n");
    printf("(1) Generate\n");
    printf("(2) Generate __# of times\n");
    printf("(3) Save\n");
    printf("(4) Load\n");
    printf("(5) Create empty 10x10 board\n");
    printf("(6) Spawn a cell at X, Y (1 to n)\n");
    printf("(7) Quit\n ");
    printf("\n");

    fgets(c, 3, stdin);
    selection = atoi(c);
    return selection;
}

/**
 * Loops through 2D array and prints each element.
 * @param r int Number of rows
 * @param c int Number of columns
 */
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
    printf("\n");
}

/**
 * Funnels 2D array characters into 1-D array
 * to be sent to write_file. '.' Indicates the end
 * of a row, which is used to restructure the board in
 * loadBoard().
 * @return int 0 if successful
 */
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
    return 0;
}

/**
 * This function gives read_file a string to fill from
 * file. Row and column sizes are then determined to build
 * the 2D array.
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

        /* Number of characters before a period = col size. */
        while (str[col] != '.') {
            col++;
        }
        /* Number of periods is the row size. */
        for (i = 0; i < size; i++) {
            if (str[i] == '.') {
                row++;
            }
        }

        freeBoard(); // Clear out previous board, if it exists
        createBoard(row, col);
        /* Fill the board. Since row and col are accurate to the
         * board size, but the file string is formatted with a
         * column of line endings, we must adjust for the extra column.*/
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

/**
 * Board is the address to an array of addresses,
 * each of which is an address to the first element
 * of an array.
 * @param r const int Number of rows
 * @param c const int NUmber of columns
 */
void createBoard(const int r, const int c) {
    int i, j;
    row = r;
    col = c;
    if (board != NULL) {
        freeBoard();
    }
    board = (char **)malloc(row * sizeof(char*));
    tempBoard = (char **)malloc(row * sizeof(char*));
    for (i = 0; i < row; i++) {
        board[i] = (char*)malloc(col * sizeof(char));
        tempBoard[i] = (char*)malloc(col * sizeof(char));
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            board[i][j] = DEAD;
            tempBoard[i][j] = DEAD;
        }
    }
}

/**
 * Spawns a cell at the specified location between 1 to n inclusive.
 * @param x const int x coordinate
 * @param y const int y coordinate
 * @return int 0 if successful
 */
int spawnCell(const int x, const int y) {
    if (board == NULL) {
        printf("There's no board yet.\n");
        return 1;
    } else if (row < y || col < x || y < 1 || x < 1) {
        printf("Outside of board boundaries X: (1 through %d) "
                       "Y: (1 through %d)\n", col, row);
        return 1;
    } else {
        printf("%d %d\n", x, y);
        board[y - 1][x - 1] = LIVE;
    }
    printBoard(row, col);
    return 0;
}

/**
 * Free dynamically allocated board and tempBoard
 * unless they do not exist.
 */
void freeBoard() {
    int i;
    if (board != NULL) {
        for (i = 0; i < row; i++) {
            free(board[i]);
        }
        free(board);
    }
    if (tempBoard != NULL) {
        for (i = 0; i < row; i++) {
            free(tempBoard[i]);
        }
        free(tempBoard);
    }
}