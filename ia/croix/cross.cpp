/*
  BRBARA is a Rule Based Area Restrainned Algo
*/

// TODO: Make everything prettier
// TODO: ADD CHECK FOR NEAR LOSSES

// TODO: Optimise all possible loops
// TODO: Find better names for all variables
// TODO: Make documentation a easier to read
// TODO: Explain the steps of the algorithm

#include "../../morpion.h"
#include <cstdio>
#define PLAYER_X 'X'
#define PLAYER_O 'O'

// NOTE: Search area is rounded to the nearest odd integer
const unsigned short zone_recherche = 5;
const short zone_recherche_offset = zone_recherche / 2;

inline unsigned positiveMod(int a, int b) {
  return (a%b+b)%b;
};


/*

Place un pion

*/
void jouerCroix(char **tab, int size) {
  unsigned most_dangerous_x = 0;
  unsigned most_dangerous_y = 0;
  unsigned highest_danger_found = 0;

  // TODO: Optimise using only one loop
  for (unsigned y = 0; y < size; y++) {
    for (unsigned x = 0; x < size; x++) {
      // We want to search around circles
      if ((tab[y][x]) != PLAYER_O) {
        continue;
      }

      printf("[CROSS] Found O at line %d col %d\n", y,x);
      // TODO: Optimise using a single loop
      // Look for the highest danger in a predefined subgrid
      for (short sub_y = -zone_recherche_offset; sub_y <= zone_recherche_offset; sub_y++) {
        for (short sub_x = -zone_recherche_offset; sub_x <= zone_recherche_offset; sub_x++) {
            const int pos_x = x+sub_x;
            const int pos_y = y+sub_y;          
            unsigned danger = 0;
            // Check for valid positions, you wouldn't access out of bounds memory ?
            if (pos_x < 0 || pos_x >= size || pos_y < 0 || pos_y >= size) continue;
            // Don't process slot if something is already on it
            if (tab[pos_y][pos_x] == 'X' ||tab[pos_y][pos_x] == 'O' ) continue;
            
            // calculate danger
            // Score system
            // A ligne is considered to be an alignement of zone_recherche slots
            // 2pt for each O on the line
            // 3pt for each near loss

            // TODO: Find a way (if any) to elinate code duplication
            // look ahead for 'O's
            printf("[DEBUG] --------Applying rules on line %d col %d-------\n", pos_y,pos_x);
            printf("[DEBUG]   --------------Looking forward\n");
            
            for (int i = sub_x;i<=zone_recherche_offset;i++) {
              if (tab[pos_y][positiveMod(pos_x+i, size)] == PLAYER_O) {
                printf("[RULE] Found Player O at line %d col %d DANGER ++\n", pos_y, positiveMod(pos_x+i, size));
                danger +=2;
              }
            }

            printf("[DEBUG]   --------------Looking backward\n");
            // look backward for 'O's}
            for (int i = sub_x;i>=-zone_recherche_offset;i--){
              if (tab[pos_y][positiveMod(pos_x+i, size)] == PLAYER_O) {
                printf("[RULE] Found Player O at line %d col %d DANGER ++\n", pos_y, positiveMod(pos_x+i, size));
                danger +=2;
              }
            }

            printf("[DEBUG]   --------------Looking on bottom\n");
            // look on bottom for 'O's
            for (int i = sub_y;i<=zone_recherche_offset;i++) {
              if (tab[positiveMod(pos_y+i,size )][pos_x] == PLAYER_O) {
                printf("[RULE] Found Player O at line %d col %d DANGER ++\n", positiveMod(pos_y+i,size ), pos_x);
                danger +=2;
              }
            }

            printf("[DEBUG]   --------------Looking on top\n");
            // look top for 'O's
            for (int i = sub_y;i>=-zone_recherche_offset;i--){
              if (tab[positiveMod(pos_y+i,size )][pos_x] == PLAYER_O) {
                printf("[RULE] Found Player O at line %d col %d DANGER ++\n", positiveMod(pos_y+i,size ), pos_x);
                danger +=2;
              }
            }

            printf("[DEBUG]   --------------Looking on part 4 of the diagonal\n");
            // bottom part of the left diagonal
            int i = sub_x;
            int j = sub_y;
            while (i<=zone_recherche_offset && j<=zone_recherche_offset) {
              // printf("[RULE] Found Looking at line %d col %d\n",positiveMod(pos_y+j, size),positiveMod(pos_x+i, size));
              if (tab[positiveMod(pos_y+j, size)][positiveMod(pos_x+i, size)] == PLAYER_O) {
                printf("[RULE] Found Player O at line %d col %d DANGER ++\n", positiveMod(pos_y+j,size ), positiveMod(pos_x+i, size));
                danger +=2;
              }
              i++;
              j++;
            }

            printf("[DEBUG]   --------------Looking on part 2 of the diagonal\n");
            // top part of the right diagonal
            i = sub_x;
            j = sub_y;
            while (i<=zone_recherche_offset && j>=-zone_recherche_offset) {
              // printf("[RULE] Found Looking at line %d col %d\n",positiveMod(pos_y+j, size),positiveMod(pos_x+i, size));
              if (tab[positiveMod(pos_y+j, size)][positiveMod(pos_x+i, size)] == PLAYER_O) {
                printf("[RULE] Found Player O at line %d col %d DANGER ++\n", positiveMod(pos_y+j,size ), positiveMod(pos_x+i, size));
                danger +=2;
              }
              i++;
              j--;
            }

            printf("[DEBUG]   --------------Looking on part 3 of the diagonal\n");
            // top part of the left diagonal
            i = sub_x;
            j = sub_y;
            while (i>=-zone_recherche_offset && j<=zone_recherche_offset) {
              // printf("[RULE] Found Looking at line %d col %d\n",positiveMod(pos_y+j, size),positiveMod(pos_x+i, size));
              if (tab[positiveMod(pos_y+j, size)][positiveMod(pos_x+i, size)] == PLAYER_O) {
                printf("[RULE] Found Player O at line %d col %d DANGER ++\n", positiveMod(pos_y+j,size ), positiveMod(pos_x+i, size));
                danger +=2;
              }
              i--;
              j++;
            }

            printf("[DEBUG]   --------------Looking on part 1 of the diagonal\n");
            // top part of the left diagonal
            i = sub_x;
            j = sub_y;
            while (i>=-zone_recherche_offset && j>=-zone_recherche_offset) {
              // printf("[RULE] Found Looking at line %d col %d\n",positiveMod(pos_y+j, size),positiveMod(pos_x+i, size));
              if (tab[positiveMod(pos_y+j, size)][positiveMod(pos_x+i, size)] == PLAYER_O) {
                printf("[RULE] Found Player O at line %d col %d DANGER ++\n", positiveMod(pos_y+j,size ), positiveMod(pos_x+i, size));
                danger +=2;
              }
              i--;
              j--;
            }

            // tab[pos_y][pos_x] = danger+48; // Rendering the subgrid with each danger
            // printf("[DEBUG] line %d col %d DANGER %d\n", pos_y, pos_x, danger);
            printf("[DEBUG] ------------------DANGER %d-------------------\n", danger);
            // compare danger with saved highest, we just want the highest danger in the whole grid
            if (danger >= highest_danger_found) {
              highest_danger_found = danger;
              most_dangerous_x = pos_x;
              most_dangerous_y = pos_y;
          }
        }
      }
    }
  }
  printf("[CROSS] Playing at line %d col %d\n", most_dangerous_y, most_dangerous_x);
  placer_morpion(tab, size, most_dangerous_y, most_dangerous_x, PLAYER_X);
}
