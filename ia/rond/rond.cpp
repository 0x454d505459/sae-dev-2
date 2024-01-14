#include <iostream>
#include <time.h>
#include <vector>
#include "../../morpion.h"

using namespace std;

/*
DEBUG
cout<<"-----------  Debug  :\ncpt_x - "<<cpt_x<<"\ncpt_y - "<<cpt_y<<"\ncpt_rond - "<<cpt_rond<<"\ncpt_espace - "<<cpt_espace<<"\nlongueur - "<<longueur<<"\npos_x - "<<pos_x<<"\npos_y - "<<pos_y<<"\ni - "<<i<<"\nj - "<<j<<endl;
*/

void JouerRond(char** tab, int size) {
	srand(time(NULL));

    bool est_vide=true;

    int cpt_x=0;
    int cpt_y=0;
    int cpt_rond=0;
    int cpt_espace=0;

    int longueur=0;
    int pos_x=-1;
    int pos_y=-1;
    for (int i=0; i<size; ++i) {  // Parcours du tableau
        for (int j=0; j<size; ++j) {
            if (tab[i][j]=='O') est_vide=false;  // Si le tableau contient une valeur X ou O, il n'est pas vide

            else if (tab[i][j]==' ') {
                // ----------------------
                cpt_x=i;
                cpt_y=j;
                cpt_rond=0;
                while (cpt_x+1<size) {  // ligne droite x+
                    if (tab[cpt_x+1][j]=='O') {
                        cpt_rond++;
                        cpt_x++;
                    }
                    else break;
                }
                cpt_x=i;
                cpt_y=j;
                cpt_espace=0;
                if (cpt_rond>longueur) {
                    while (cpt_x-1>=0) {
                        if (tab[cpt_x-1][j]!='X') {  // x-
                            cpt_espace++;
                            cpt_x--;
                        }
                        else break;
                    }
                    if (cpt_rond+cpt_espace>4) {
                        longueur=cpt_rond;
                        pos_x=i;
                        pos_y=j;
                    }
                }
                // ----------------------
                cpt_x=i;
                cpt_y=j;
                cpt_rond=0;
                while (cpt_x-1>=0) {  // ligne gauche x-
                    if (tab[cpt_x-1][j]=='O') {
                        cpt_rond++;
                        cpt_x--;
                    }
                    else break;
                }
                cpt_x=i;
                cpt_y=j;
                cpt_espace=0;
                    if (cpt_rond>longueur) {
                    while (cpt_x+1<size) {
                        if (tab[cpt_x+1][j]!='X') {  // x+
                            cpt_espace++;
                            cpt_x++;
                        }
                        else break;
                    }
                    if (cpt_rond+cpt_espace>4) {
                        longueur=cpt_rond;
                        pos_x=i;
                        pos_y=j;
                    }
                }
                // ----------------------
                cpt_x=i;
                cpt_y=j;
                cpt_rond=0;
                while (cpt_y-1>=0) {  // colonne haut y-
                    if (tab[i][cpt_y-1]=='O') {
                        cpt_rond++;
                        cpt_y--;
                    }
                    else break;
                }
                cpt_x=i;
                cpt_y=j;
                cpt_espace=0;
                if (cpt_rond>longueur) {
                    while (cpt_y+1<size) {
                        if (tab[i][cpt_y+1]!='X') {  // y+
                            cpt_espace++;
                            cpt_y++;
                        }
                        else break;
                    }
                    if (cpt_rond+cpt_espace>4) {
                        longueur=cpt_rond;
                        pos_x=i;
                        pos_y=j;
                    }
                }
                // ----------------------
                cpt_x=i;
                cpt_y=j;
                cpt_rond=0;
                while (cpt_y+1<size) {  // colonne bas y+
                    if (tab[i][cpt_y+1]=='O') {
                        cpt_rond++;
                        cpt_y++;
                    }
                    else break;
                }
                cpt_x=i;
                cpt_y=j;
                cpt_espace=0;
                if (cpt_rond>longueur) {
                    while (cpt_y-1>=0) {
                        if (tab[i][cpt_y-1]!='X') {  // y-
                            cpt_espace++;
                            cpt_y--;
                        }
                        else break;
                    }
                    if (cpt_rond+cpt_espace>4) {
                        longueur=cpt_rond;
                        pos_x=i;
                        pos_y=j;
                    }
                }
                // ----------------------
                cpt_x=i;
                cpt_y=j;
                cpt_rond=0;
                while (cpt_x+1<size && cpt_y+1<size) {  // diagonal 🡾 x+ y+
                    if (tab[cpt_x+1][cpt_y+1]=='O') {
                        cpt_rond++;
                        cpt_x++;
                        cpt_y++;
                    }
                    else break;
                }
                cpt_x=i;
                cpt_y=j;
                cpt_espace=0;
                if (cpt_rond>longueur) {
                    while (cpt_x-1>=0 && cpt_y-1>=0) {
                        if (tab[cpt_x-1][cpt_y-1]!='X') {  // x- y-
                            cpt_espace++;
                            cpt_x--;
                            cpt_y--;
                        }
                        else break;
                    }
                    if (cpt_rond+cpt_espace>4) {
                        longueur=cpt_rond;
                        pos_x=i;
                        pos_y=j;
                    }
                }
                // ----------------------
                cpt_x=i;
                cpt_y=j;
                cpt_rond=0;
                while (cpt_x-1>=0 && cpt_y-1>=0) {  // diagonal 🡼 x- y-
                    if (tab[cpt_x-1][cpt_y-1]=='O') {
                        cpt_rond++;
                        cpt_x--;
                        cpt_y--;
                    }
                    else break;
                }
                cpt_x=i;
                cpt_y=j;
                cpt_espace=0;
                if (cpt_rond>longueur) {
                    while (cpt_x+1<size && cpt_y+1<size) {
                        if (tab[cpt_x+1][cpt_y+1]!='X') {  // x+ y+
                            cpt_espace++;
                            cpt_x++;
                            cpt_y++;
                        }
                        else break;
                    }
                    if (cpt_rond+cpt_espace>4) {
                        longueur=cpt_rond;
                        pos_x=i;
                        pos_y=j;
                    }
                }
                // ----------------------
                cpt_x=i;
                cpt_y=j;
                cpt_rond=0;
                while (cpt_x+1<size && cpt_y-1>=0) {  // diagonal 🡽 x+ y-
                    if (tab[cpt_x+1][cpt_y-1]=='O') {
                        cpt_rond++;
                        cpt_x++;
                        cpt_y--;
                    }
                    else break;
                }
                cpt_x=i;
                cpt_y=j;
                cpt_espace=0;
                if (cpt_rond>longueur) {
                    while (cpt_x-1>=0 && cpt_y+1<size) {
                        if (tab[cpt_x-1][cpt_y+1]!='X') {  // x- y+
                            cpt_espace++;
                            cpt_x--;
                            cpt_y++;
                        }
                        else break;
                    }
                    if (cpt_rond+cpt_espace>4) {
                        longueur=cpt_rond;
                        pos_x=i;
                        pos_y=j;
                    }
                }
                // ----------------------
                cpt_x=i;
                cpt_y=j;
                cpt_rond=0;
                while (cpt_x-1>=0 && cpt_y+1<size) {  // diagonal 🡿 x- y+
                    if (tab[cpt_x-1][cpt_y+1]=='O') {
                        cpt_rond++;
                        cpt_x--;
                        cpt_y++;
                    }
                    else break;
                }
                cpt_x=i;
                cpt_y=j;
                cpt_espace=0;
                if (cpt_rond>longueur) {
                    while (cpt_x+1<size && cpt_y-1>=0) {
                        if (tab[cpt_x+1][cpt_y-1]!='X') {  // x+ y-
                            cpt_espace++;
                            cpt_x++;
                            cpt_y--;
                        }
                        else break;
                    }
                    if (cpt_rond+cpt_espace>4) {
                        longueur=cpt_rond;
                        pos_x=i;
                        pos_y=j;
                    }
                }
                // ----------------------
            }
        }
    }
    
    if (est_vide==true || (pos_x==-1 && pos_y==-1)) { // Si le tableau est vide
        int x=-1;
        int y=-1;
        while (!estLibre_morpion(tab, size, x, y)) {  // Place dans un endroit propice
            x=(rand() % 7)+5;
            y=(rand() % 7)+5;
        }
        placer_morpion(tab,size,x,y,'O');
        cout<<"Placement en :\nx - "<<x<<"\ny - "<<y<<endl;
    }
    else {
        placer_morpion(tab,size,pos_x,pos_y,'O');
        cout<<"Placement en :\nx - "<<pos_x<<"\ny - "<<pos_y<<endl;
    }
}