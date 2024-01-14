#include "../../../morpion.h"

void jouerIA(char** tab, int& x, int& y, int size, char pion) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (estLibre_morpion(tab, size, i, j)) {
                placer_morpion(tab, size, i, j, pion);
                bool victoire = victoire_morpion(tab, size, 5, pion);
                tab[i][j] = ' '; // ?
                if (victoire) {
                    x = i;  
                    y = j; 
                    return;
                }
            }
        }
    }
    char adversaire = (pion == 'X') ? 'O' : 'X';

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (estLibre_morpion(tab, size, i, j)) {
                placer_morpion(tab, size, i, j, adversaire);
                bool victoire = victoire_morpion(tab, size, 5, adversaire);
                tab[i][j] = ' ';
                if (victoire) {
                    x = i;
                    y = j;
                    return;
                }
            }
        }
    }

    do {
        x = rand() % size;
        y = rand() % size;
    } while (!estLibre_morpion(tab, size, x, y));
} 
