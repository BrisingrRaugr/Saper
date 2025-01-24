#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100  // maksymalny rozmiar planszy (100 x 100)


void initBoard(Cell board[N][N], int n, int m) {
    // Ustawienie pol
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            board[i][j].mine = 0;
            board[i][j].revealed = 0;
            board[i][j].flagged = 0;
            board[i][j].adjacentMines = 0;
        }
    }
}

// Funkcja do losowania min, uwzgledniajaca pierwszy wybor gracza
void placeMines(Cell board[N][N], int firstRow, int firstCol, int mines, int n, int m) {
    int placed = 0;
      srand(time(NULL));
    while (placed < mines) {
        int row = rand() % n;
        int col = rand() % m;
        // Upewniamy sie, ze mina nie pojawi sie w miejscu pierwszego odkrycia
        if ((row != firstRow || col != firstCol) && board[row][col].mine == 0) {
            board[row][col].mine = 1;
            placed++;
        }
    }
}

// Funkcja do obliczania liczby min w sasiedztwie
void calculateAdjacentMines(Cell board[N][N], int n, int m) {
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1}, {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j].mine == 1) continue;
            int count = 0;
            for (int k = 0; k < 8; k++) {
                int ni = i + directions[k][0];
                int nj = j + directions[k][1];
                if (ni >= 0 && ni < n && nj >= 0 && nj < n && board[ni][nj].mine == 1) {
                    count++;
                }
            }
            board[i][j].adjacentMines = count;
        }
    }
}

// Funkcja do wyswietlania planszy
void printBoard(Cell board[N][N], int reveal, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j].flagged) {
                printf("F ");
            } else if (board[i][j].revealed|| reveal==1) {
                if (board[i][j].mine) {
                    printf("b ");
                } else {
                    printf("%d ", board[i][j].adjacentMines);
                }
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
}

// Funkcja do odkrywania pola
int revealCell(Cell board[N][N], int row, int col, int n, int m) {
   if (row < 0 || row >= n || col < 0 || col >= m || board[row][col].revealed || board[row][col].flagged) {
        return 0;
    }
    int points=0;
    board[row][col].revealed = 1;
    if (board[row][col].adjacentMines == 0) {
        // Odkrywamy sasiednie pola
        int directions[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1}, {0, 1},
            {1, -1}, {1, 0}, {1, 1}
        };
        for (int i = 0; i < 8; i++) {
            int ni = row + directions[i][0];
            int nj = col + directions[i][1];
            if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
               points+=revealCell(board, ni, nj, n, m);
            }
        }
    }
    return points+1;
}

// Funkcja do obslugi flagowania
void flagCell(Cell board[N][N], int row, int col, int n, int m) {
    if (row >= 0 && row < n && col >= 0 && col < m && !board[row][col].revealed) {
        board[row][col].flagged = !board[row][col].flagged;
    }
}

// Funkcja do sprawdzenia, czy gra siê zakoñczy³a
int checkWin(Cell board[N][N], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!board[i][j].mine && !board[i][j].revealed) {
                return 0;  // Gra nie skoñczona
            }
        }
    }
    return 1;  // Gra zakoñczona
}
