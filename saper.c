#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "scores.h"
#include "maze.h"

#define N 100  // maksymalny rozmiar planszy (100 x 100)
#define MAX_RESULTS 5

int main() {

    int firstMove = 1;
     Cell board[N][N];
    int gameOver = 0;
    int firstRow, firstCol;
    int score=0;
    int multiply = 0;
    int n, m, mines;
    char choice;
    printf("Podaj poziom trudnosci( 1 - latwy, 2 - normalny, 3 - trudny, 4 - wlasny).\n");
    scanf("%c", &choice);
    if(choice=='1')
    {
        n=9;
        m=9;
        mines=10;
        multiply = 1;
    }
    else if(choice=='2')
    {
        n=16;
        m=16;
        mines=40;
         multiply = 2;
    } else
    if(choice=='3')
    {
        n=16;
        m=30;
        mines=99;
         multiply = 3;
    }
    else
    {
        printf("Podaj wlasne parametry ( ilosc wierszy, ilosc kolumn, ilosc min) .\n");
        scanf("%d %d %d", &n, &m, &mines);
    }
    initBoard(board, n, m);
    Score scores[MAX_RESULTS] = {{0}};
    loadScores(scores);
 printBoard(board, 0, n, m);
    while (!gameOver) {
        scanf("%c", &choice);
        if (choice == 'x') break;
        int row, col;
        scanf("%d %d", &row, &col);

        // Pierwszy ruch gracza
        if (firstMove) {
            firstRow = row;
            firstCol = col;
            placeMines(board, firstRow, firstCol, mines, n,  m);  // Umieszczamy miny, omijaj¹c pierwsze wybrane pole
            calculateAdjacentMines(board, n, m);  // Obliczamy liczby min w s¹siedztwie
            firstMove = 0;  // Pierwszy ruch zosta³ wykonany
        }

        if (choice == 'r') {
            if (board[row][col].mine) {
                    board[row][col].revealed=1;
                    printBoard(board, 0, n, m);
                printf("Bum! Trafiles na mine. Gra skonczona.\n");
                gameOver = 1;

            } else {
                score+=multiply*revealCell(board, row, col, n, m);
                 printBoard(board, 0, n, m);
                if (checkWin(board, n, m)) {
                    printf("Gratulacje, wygrales!\n");
                    gameOver = 1;

                }
            }
        } else if (choice == 'f') {
            flagCell(board, row, col, n, m);
              printBoard(board, 0, n, m);
        }
        else if (choice == 'c')
        {
             printBoard(board, 1, n, m);
        }
    }
    printf("Twoj wynik to: %d\n",score);

       if (score > 0) {
             char playerName[30];



    printf("\nPodaj swoje imie: ");
    scanf("%s", playerName);

        displayScores(scores);
        // Dodanie wyniku gracza
        Score newScore = {0};
        strcpy(newScore.name, playerName);
        newScore.score = score;

        // Dodajemy wynik do tablicy i sortujemy
        scores[MAX_RESULTS - 1] = newScore;
        sortScores(scores);

        // Zapisanie najlepszych wyników do pliku
        saveScores(scores);

    }

    return 0;
}
