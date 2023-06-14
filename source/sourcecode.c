#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char PLAYER = 'X';
char COMPUTER = 'O';
char winner = ' ';

char board[3][3];
int rows = sizeof(board) / sizeof(board[0]);
int columns = sizeof(board[0]) / sizeof(board[0][0]);
int selectedRow;
int selectedColumn;
int slotsLeft;

void resetBoard();
void printBoard();
void promptUser();
void computerMove();
void checkWinner();

int main() {
    resetBoard();
    promptUser();

    return 0;
}

void resetBoard() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }

    slotsLeft = 9;
    printBoard();
}

void printBoard() {
    printf("\n %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---");
    printf("\n %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---");
    printf("\n %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

void promptUser() {
    int selectedRow, selectedColumn;
    printf("\nEnter a # (row): ");

    if (scanf("%d", &selectedRow) != 1) {
        printf("\nInvalid input! Please enter a valid integer.\n");
        while (getchar() != '\n');
        promptUser();
        return;
    }

    selectedRow--;

    printf("\nEnter a # (column): ");

    if (scanf("%d", &selectedColumn) != 1) {
        printf("\nInvalid input! Please enter a valid integer.\n");
        while (getchar() != '\n');
        promptUser();
        return;
    }

    selectedColumn--;

    if (board[selectedRow][selectedColumn] == ' ') {
        board[selectedRow][selectedColumn] = PLAYER;
        slotsLeft--;
        printBoard();

        checkWinner();

        computerMove();
    }
    else {
        printf("\nInvalid move!\n");
        promptUser();
    }
}

void computerMove() {
    srand(time(0));

    int randomRow = rand() % rows;
    int randomColumn = rand() % columns;

    while (board[randomRow][randomColumn] != ' ') {
        randomRow = rand() % rows;
        randomColumn = rand() % columns;
    }

    printf("\nComputer played!\n");
    board[randomRow][randomColumn] = COMPUTER;
    slotsLeft--;
    printBoard();

    checkWinner();

    promptUser();
}

void checkWinner() {
    // Check rows
    for (int i = 0; i < rows; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            winner = board[i][0];
            printf("\n%c wins!\n", winner);
            exit(0);
        }
    }

    // Check columns
    for (int j = 0; j < columns; j++) {
        if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            winner = board[0][j];
            printf("\n%c wins!\n", winner);
            exit(0);
        }
    }

    // Check diagonals
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        winner = board[0][0];
        printf("\n%c wins!\n", winner);
        exit(0);
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        winner = board[0][2];
        printf("\n%c wins!\n", winner);
        exit(0);
    }

    // Check for a draw
    if (slotsLeft == 0) {
        printf("\nIt's a draw!\n");
        exit(0);
    }
}
