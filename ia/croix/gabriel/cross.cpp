/*
  BRBARA is a Rule Based Area Restrainned Algo
*/

// TODO: ADD CHECK FOR NEAR LOSSES

#include "../../../morpion.h"
#include "./debug_utils.cpp"
#include "./rules.cpp"
#include <iostream>
#define PLAYER_X 'X'
#define PLAYER_O 'O'

// NOTE: Search area is rounded to the nearest odd integer
inline const unsigned short zone_recherche = 5;
inline const short zone_recherche_offset = zone_recherche / 2 + 1;

/*

Place un pion

*/
void jouerCroix(char **tab, int size) {
  unsigned most_dangerous_x = 0;
  unsigned most_dangerous_y = 0;
  unsigned highest_danger_found = 0;

#ifdef ShowHeatmap
  char** heatmap = copie_morpion(tab, size);
#endif
  // TODO: Optimise using only one loop
  for (unsigned line = 0; line < size; line++) {
    for (unsigned column = 0; column < size; column++) {
      // We want to search around circles
      if ((tab[line][column]) != PLAYER_O) {
        continue;
      }

#ifdef DebugLvlLight
      printf("[CROSS][DEBUG] Found O at line %d col %d\n", line,column);
#endif
      // Look for the highest danger in a predefined subgrid
      for (short sub_y = -zone_recherche_offset; sub_y <= zone_recherche_offset; sub_y++) {
        for (short sub_x = -zone_recherche_offset; sub_x <= zone_recherche_offset; sub_x++) {
            const int offset_column = column+sub_x;
            const int offset_line = line+sub_y;          
            unsigned danger = 0;
            unsigned calculated_danger = 0;
            unsigned consecutive_Os = 0;
            // Check for valid positions, you wouldn't access out of bounds memory ?
            if (offset_column < 0 || offset_column >= size || offset_line < 0 || offset_line >= size) continue;
            // Don't process slot if something is already on it
            if (tab[offset_line][offset_column] == PLAYER_X ||tab[offset_line][offset_column] == PLAYER_O ) continue;
#ifdef DebugLvlLight
            printf("[DEBUG][CROSS] --------Applying rules on line %d col %d-------\n", offset_line,offset_column);
#endif            
            dangerAhead(tab, size, danger, calculated_danger, consecutive_Os, sub_x,sub_y,offset_line,offset_column, zone_recherche_offset);
            dangerBackward(tab, size, danger, calculated_danger, consecutive_Os, sub_x,sub_y,offset_line,offset_column, zone_recherche_offset);

            dangerConsecutive(danger, consecutive_Os);

            dangerBottom(tab, size, danger, calculated_danger, consecutive_Os, sub_x,sub_y,offset_line,offset_column, zone_recherche_offset);
            dangerTop(tab, size, danger, calculated_danger, consecutive_Os, sub_x,sub_y,offset_line,offset_column, zone_recherche_offset);

            dangerConsecutive(danger, consecutive_Os);

            dangerDiagonalQuarter1(tab, size, danger, calculated_danger, consecutive_Os, sub_x,sub_y,offset_line,offset_column, zone_recherche_offset);
            dangerDiagonalQuarter4(tab, size, danger, calculated_danger, consecutive_Os, sub_x,sub_y,offset_line,offset_column, zone_recherche_offset);

            dangerConsecutive(danger, consecutive_Os);

            dangerDiagonalQuarter2(tab, size, danger, calculated_danger, consecutive_Os, sub_x,sub_y,offset_line,offset_column, zone_recherche_offset);
            dangerDiagonalQuarter3(tab, size, danger, calculated_danger, consecutive_Os, sub_x,sub_y,offset_line,offset_column, zone_recherche_offset);
          
            dangerConsecutive(danger, consecutive_Os);
            
#ifdef ShowHeatmap
            if (tab[offset_line][offset_column] != PLAYER_O || tab[offset_line][offset_column] != PLAYER_X){
              heatmap[offset_line][offset_column] = danger; // Rendering the subgrid with each danger
            }
#endif
#ifdef DebugLvlLight
            printf("[DEBUG][CROSS] ------------------DANGER %d-------------------\n", danger);
#endif
            // compare danger with saved highest, we just want the highest danger in the whole grid
            if (danger >= highest_danger_found) {
              highest_danger_found = danger;
              most_dangerous_x = offset_column;
              most_dangerous_y = offset_line;
          }
        }
      }
    }
  }
#ifdef ShowHeatmap
  showHeatmap(heatmap, size);
#endif
  printf("[CROSS] Playing at line %d col %d\n", most_dangerous_y, most_dangerous_x);
  placer_morpion(tab, size, most_dangerous_y, most_dangerous_x, PLAYER_X);
}
