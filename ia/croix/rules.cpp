#define PLAYER_X 'X'
#define PLAYER_O 'O'
#include <algorithm>
#include <iostream>

/*
@brief This is the rule set the whole algorithm relies upon

RULES:
- For each enemy (PLAYER_O) on the line we increase the danger by 1
  as well as add 1 to the number of consecutive Os

- if an X is present on the line, then this one cannot be completed
  so don't bother continuing it and danger is nul here, consecutive Os
  are broken appart

- If we find a space then no there's no consecutive Os

*/
bool baseDangerCalculation(char player_at, unsigned &calculated_danger,
                           unsigned &danger, unsigned consecutive_Os) {
  if (player_at == PLAYER_O) {
    calculated_danger += 1;
    consecutive_Os++;
#ifdef DebugLvlMedium
    printf("[DEBUG][CROSS] Found PLAYER_O, Danger ++\n");
#endif
  } else if (player_at == PLAYER_X) {
    consecutive_Os = 0;
    calculated_danger = 0;
#ifdef DebugLvlMedium
    printf("[DEBUG][CROSS] Found PLAYER_X, Danger 0\n");
#endif

    return 0;
  } else {
    consecutive_Os = 0;
  }
  danger += calculated_danger;
  calculated_danger = 0;
  return 1;
}

extern void dangerConsecutive(unsigned &danger, unsigned consecutive_Os) {
  // if we have 2 or more consecutive Os increase danger,
  // player is more likely to finish this line
  danger += (consecutive_Os) * (consecutive_Os > 1);
  // printf("danger+=%u",(consecutive_Os)*(consecutive_Os>1));
  consecutive_Os = 0;
}

// ---------------------------------- SEARCH SECTION --------------------------------------------

extern void dangerAhead(char **tab, int size, unsigned &danger,
                        unsigned &calculated_danger, unsigned &consecutive_Os,
                        short sub_x, short sub_y, int offset_line,
                        int offset_column, short zone_recherche_offset) {

#ifdef DebugLvlMedium
  printf("[DEBUG][CROSS]   --------------Looking forward\n");
#endif
  for (int i = sub_x; i >= -zone_recherche_offset; i--) {
    const char player_at =
        tab[offset_line][std::clamp(offset_column + i,0, size - 1)];
    if (!baseDangerCalculation(player_at, calculated_danger, danger,
                               consecutive_Os))
      break;
  }
}

extern void dangerBackward(char **tab, int size, unsigned &danger,
                           unsigned &calculated_danger,
                           unsigned &consecutive_Os, short sub_x, short sub_y,
                           int offset_line, int offset_column,
                           short zone_recherche_offset) {

#ifdef DebugLvlMedium
  printf("[DEBUG][CROSS]   --------------Looking backward\n");
#endif
  for (int i = sub_x; i <= zone_recherche_offset; i++) {
    const char player_at =
        tab[offset_line][std::clamp(offset_column + i, 0, size - 1)];
    if (!baseDangerCalculation(player_at, calculated_danger, danger,
                               consecutive_Os))
      break;
  }
}

extern void dangerBottom(char **tab, int size, unsigned &danger,
                         unsigned &calculated_danger, unsigned &consecutive_Os,
                         short sub_x, short sub_y, int offset_line,
                         int offset_column, short zone_recherche_offset) {

#ifdef DebugLvlMedium
  printf("[DEBUG][CROSS]   --------------Looking on bottom\n");
#endif
  for (int i = sub_y; i >= -zone_recherche_offset; i--) {
    const char player_at =
        tab[std::clamp(offset_line + i, 0, size - 1)][offset_column];
    if (!baseDangerCalculation(player_at, calculated_danger, danger,
                               consecutive_Os))
      break;
  }
}

extern void dangerTop(char **tab, int size, unsigned &danger,
                      unsigned &calculated_danger, unsigned &consecutive_Os,
                      short sub_x, short sub_y, int offset_line,
                      int offset_column, short zone_recherche_offset) {
#ifdef DebugLvlMedium
  printf("[DEBUG][CROSS]   --------------Looking on top\n");
#endif
  for (int i = sub_y; i <= zone_recherche_offset; i++) {
    const char player_at =
        tab[std::clamp(offset_line + i,0, size - 1)][offset_column];
    if (!baseDangerCalculation(player_at, calculated_danger, danger,
                               consecutive_Os))
      break;
  }
}

extern void dangerDiagonalQuarter1(char **tab, int size, unsigned &danger,
                                   unsigned &calculated_danger,
                                   unsigned &consecutive_Os, short sub_x,
                                   short sub_y, int offset_line,
                                   int offset_column,
                                   short zone_recherche_offset) {
#ifdef DebugLvlMedium
  printf("[DEBUG][CROSS]   --------------Looking on quarter 1 of the diagonal\n");
#endif
  int i = sub_x;
  int j = sub_y;
  while (i <= zone_recherche_offset && j <= zone_recherche_offset) {
    const char player_at = tab[std::clamp(offset_line + j, 0, size-1)]
                              [std::clamp(offset_column + i, 0, size-1)];
    if (!baseDangerCalculation(player_at, calculated_danger, danger,
                               consecutive_Os))
      break;
    i++;
    j++;
  }
}

extern void dangerDiagonalQuarter2(char **tab, int size, unsigned &danger,
                                   unsigned &calculated_danger,
                                   unsigned &consecutive_Os, short sub_x,
                                   short sub_y, int offset_line,
                                   int offset_column,
                                  short zone_recherche_offset) {
#ifdef DebugLvlMedium
  printf("[DEBUG][CROSS]   --------------Looking on quarter 2 of the diagonal\n");
#endif
  int i = sub_x;
  int j = sub_y;
  while (i >= -zone_recherche_offset && j <= zone_recherche_offset) {
    const char player_at = tab[std::clamp(offset_line + j, 0, size-1)]
                              [std::clamp(offset_column + i, 0, size-1)];
    if (!baseDangerCalculation(player_at, calculated_danger, danger,
                               consecutive_Os))
      break;
    i--;
    j++;
  }
}

extern void dangerDiagonalQuarter3(char **tab, int size, unsigned &danger,
                                   unsigned &calculated_danger,
                                   unsigned &consecutive_Os, short sub_x,
                                   short sub_y, int offset_line,
                                   int offset_column,
                                   short zone_recherche_offset) {
#ifdef DebugLvlMedium
  printf("[DEBUG][CROSS]   --------------Looking on quarter 3 of the diagonal\n");
#endif
  int i = sub_x;
  int j = sub_y;
  while (i <= zone_recherche_offset && j >= -zone_recherche_offset) {
    const char player_at = tab[std::clamp(offset_line + j, 0, size-1)]
                              [std::clamp(offset_column + i, 0, size-1)];
    if (!baseDangerCalculation(player_at, calculated_danger, danger,
                               consecutive_Os))
      break;
    i++;
    j--;
  }
}

extern void dangerDiagonalQuarter4(char **tab, int size, unsigned &danger,
                                   unsigned &calculated_danger,
                                   unsigned &consecutive_Os, short sub_x,
                                   short sub_y, int offset_line,
                                   int offset_column,
                                   short zone_recherche_offset) {
#ifdef DebugLvlMedium
  printf("[DEBUG][CROSS]   --------------Looking on quarter 4 of the diagonal\n");
#endif
  int i = sub_x;
  int j = sub_y;
  while (i >= -zone_recherche_offset && j >= -zone_recherche_offset) {
    const char player_at = tab[std::clamp(offset_line + j, 0, size-1)]
                              [std::clamp(offset_column + i, 0, size-1)];
    if (!baseDangerCalculation(player_at, calculated_danger, danger,
                               consecutive_Os))
      break;
    i--;
    j--;
  }
}
