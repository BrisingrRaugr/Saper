#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdio.h>

#define N 100  // maksymalny rozmiar planszy (100 x 100)



// Struktura do reprezentacji pola na planszy
typedef struct {
    int mine;  // 1 jeœli mina, 0 jeœli nie
    int revealed;  // 1 jeœli odkryte, 0 jeœli nie
    int flagged;  // 1 jeœli flaga, 0 jeœli nie
    int adjacentMines;  // Liczba min w s¹siedztwie
} Cell;

void initBoard(Cell board[N][N], int n, int m);

void placeMines(Cell board[N][N], int firstRow, int firstCol, int mines, int n, int m);

void calculateAdjacentMines(Cell board[N][N], int n, int m);

void printBoard(Cell board[N][N], int reveal, int n, int m);

int revealCell(Cell board[N][N], int row, int col, int n, int m);

void flagCell(Cell board[N][N], int row, int col, int n, int m);

int checkWin(Cell board[N][N], int n, int m);

#endif
