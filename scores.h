#ifndef _SCORES_H_
#define _SCORES_H_

#include <stdio.h>

#define MAX_RESULTS 5

// Struktura do przechowywania wyników
typedef struct {
    char name[30];  // Imie gracza
    int score;  // Wynik
} Score;

void saveScores(Score scores[MAX_RESULTS]);

void loadScores(Score scores[MAX_RESULTS]);

void displayScores(Score scores[MAX_RESULTS]);

void sortScores(Score scores[MAX_RESULTS]);

#endif
