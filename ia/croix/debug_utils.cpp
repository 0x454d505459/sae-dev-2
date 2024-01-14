#include <iostream>

struct Color {
  unsigned r;
  unsigned g;
  unsigned b;
};
const Color danger_low{53, 212, 98};
const Color danger_high{248, 79, 79};
inline const char hex[17] = {'0', '1', '2', '3', '4', '5', '6', '7',
                             '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '+'};

inline Color lerpColor(Color from, Color to, float amount) {
  if (amount > 1.0) {
    printf("PANIC! Amount is over 1!");
    exit(1);
  }
  return {static_cast<unsigned>(from.r * (1 - amount) + to.r * amount),
          static_cast<unsigned>(from.g * (1 - amount) + to.g * amount),
          static_cast<unsigned>(from.b * (1 - amount) + to.b * amount)};
}
/*
 Modified verion of afficherMorpion
*/
extern void showHeatmap(char **heatmap, int size) {
  std::cout << std::endl;
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (heatmap[i][j] == 'O')
        std::cout << "\033[34m " << heatmap[i][j] << " \033[0m";
      else if (heatmap[i][j] == 'X')
        std::cout << "\033[31m " << heatmap[i][j] << " \033[0m";
      else if (heatmap[i][j] == ' ')
        std::cout << "   ";
      else {
        const Color heatColor =
            lerpColor(danger_low, danger_high, (heatmap[i][j]) / 16.0);
        printf("\x1b[48;2;%u;%u;%um %c \x1b[0m", heatColor.r, heatColor.g,
               heatColor.b, hex[heatmap[i][j] % 17]);
      }
    }
    std::cout << std::endl;
  }
}
