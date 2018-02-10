#include <stdio.h>
#include <stdlib.h>
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
/*  https://www.geeksforgeeks.org/enumeration-enum-c/  */

void createBoard(int row, int col);
void printBoard();
void loadBoard();
void saveBoard();
void updateBoard(int n);
int promptUser();
int freeBoard();

int row, col;
int generations;
/*
 * Using board, determine the next game state onto board2, then overwrite
 * board with tempBoard.
 */
char **board; // 2D array
char *fileName;

int main(int argc, char const *argv[]) {

    createBoard(10, 10);
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
        switch (promptUser()) {

            case 1: // Update 1 generation
                updateBoard(1);
                break;
            case 2: // Update n generations
                printf("Number of generations: \n");
                scanf("%d", &generations);
                updateBoard(generations);
                break;
            case 3: // Save
                printf("Save as?: \n");
                scanf("%c", &fileName);
                //write_file(fileName, *board, size);
                break;
            case 4: // Load
                printf("Enter file name: \n");
                scanf("%c", &fileName);
                //read_file(fileName, **board);
                break;
            case 5: // Exit
                printf("Destroying world. How can you sleep at night? \n");
                exit(0);
        }
    }
    return 0;
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
    printBoard();
}

int promptUser() {
    int selection;

    printf("What would you like to do?\n");
    printf("(1) Generate\n");
    printf("(2) Generate __# of times\n");
    printf("(3) Save\n");
    printf("(4) Load\n");
    printf("(5) Quit\n");
    //printf("(5) Spawn life at coordinates: X Y\n");

    scanf("%d", &selection);
    return selection;
}

void printBoard() {
    // print board
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

/*Board is the address to an array of addresses,
 * each of which is an address to the first element
 * of an array.
 *
 */
void createBoard(int row, int col) {
    int i, j;

    board = (char **)malloc(row * sizeof(char*));
    for (i = 0; i < row; i++) {
        board[i] = (char*)malloc(col * sizeof(char));
    }

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            board[i][j] = '_';
        }
    }
}

int freeBoard() {
    int i;
    for (i = 0; i < row; i++) {
        free(board[i]);
    }
    free(board);
}


