#include "scores.h"

#include <stdio.h>
#include <string.h>

#define MAX_RESULTS 5

// Funkcja do zapisania wynikow do pliku
void saveScores(Score scores[MAX_RESULTS]) {
    FILE *file = fopen("scores.txt", "w");
    if (!file) {
        printf("Nie uda³o siê otworzyæ pliku!\n");
        return;
    }

    for (int i = 0; i < MAX_RESULTS; i++) {
        if (scores[i].score > 0) {  // Zapisujemy tylko te wyniki, ktore sa wiêksze niz 0
            fprintf(file, "%s %d\n", scores[i].name, scores[i].score);
        }
    }

    fclose(file);
}

// Funkcja do wczytania wynikow z pliku
void loadScores(Score scores[MAX_RESULTS]) {
    FILE *file = fopen("scores.txt", "r");
    if (!file) {
        return;  // Brak pliku, nie ma wynikow do wczytania
    }

    int i = 0;
    while (i < MAX_RESULTS && fscanf(file, "%s %d", scores[i].name, &scores[i].score) == 2) {
        i++;
    }

    fclose(file);
}

// Funkcja do wyswietlenia najlepszych wynikow
void displayScores(Score scores[MAX_RESULTS]) {
    printf("\nNajlepsze wyniki:\n");
    for (int i = 0; i < MAX_RESULTS; i++) {
        if (scores[i].score > 0) {
            printf("%d. %s - %d pkt\n", i + 1, scores[i].name, scores[i].score);
        }
    }
}

// Funkcja do sortowania wynikow
void sortScores(Score scores[MAX_RESULTS]) {
    for (int i = 0; i < MAX_RESULTS - 1; i++) {
        for (int j = i + 1; j < MAX_RESULTS; j++) {
            if (scores[i].score < scores[j].score) {
                Score temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }
}
