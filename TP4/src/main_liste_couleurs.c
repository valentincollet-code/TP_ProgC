#include <stdio.h>
#include "liste.h"

int main() {
    liste_couleurs ma_liste;
    init_liste(&ma_liste);

    // Création de quelques couleurs (Format: R, V, B, Alpha)
    couleur rouge = {0xFF, 0x00, 0x00, 0xFF};
    couleur vert  = {0x00, 0xFF, 0x00, 0xFF};
    couleur bleu  = {0x00, 0x00, 0xFF, 0xFF};
    couleur jaune = {0xFF, 0xFF, 0x00, 0xFF};
    couleur cyan    = {0x00, 0xFF, 0xFF, 0xFF};
    couleur magenta = {0xFF, 0x00, 0xFF, 0xFF};
    couleur orange  = {0xFF, 0xA5, 0x00, 0xFF};
    couleur gris    = {0x80, 0x80, 0x80, 0xFF};
    couleur rose    = {0xFF, 0xC0, 0xCB, 0xFF};
    couleur noir    = {0x00, 0x00, 0x00, 0xFF};


    // Insertion dans la liste
    insertion(&rouge, &ma_liste);
    insertion(&vert, &ma_liste);
    insertion(&bleu, &ma_liste);
    insertion(&jaune, &ma_liste);
    insertion(&cyan, &ma_liste);
    insertion(&magenta, &ma_liste);
    insertion(&orange, &ma_liste);
    insertion(&gris, &ma_liste);
    insertion(&rose, &ma_liste);
    insertion(&noir, &ma_liste);

    printf("--- Liste des couleurs enregistrées ---\n");
    parcours(&ma_liste);

    return 0;
}
