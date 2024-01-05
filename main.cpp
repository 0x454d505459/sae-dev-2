#include "morpion.h"
#include "ia/croix/cross.cpp"

int main() {

  char **tab;
  int size = 15;
  int nombre_pion_a_aligner = 5;

  init_morpion(tab, size);

  bool alignement = false;
  bool joueur = false;

  int nombre_placement_occupes = 0;

  while (!alignement && nombre_placement_occupes < size * size) {

    affichage_morpion(tab, size);

    // coordinates of the first O
    int x = 4;
    int y = 4;

    if (joueur) {
      printf("Cross time\n");
      jouerCroix(tab,size);
    }
    else {
      std::cin >> x >> y;
      std::cout << std::endl;
      placer_morpion(tab, size, x, y, 'O');

      alignement = victoire_morpion(tab, size, nombre_pion_a_aligner, 'O');
      
    }
    nombre_placement_occupes++;
    joueur = !joueur;

  }

  affichage_morpion(tab, size);
  delete_morpion(tab, size);
}
