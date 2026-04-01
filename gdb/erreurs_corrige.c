#include <stdio.h>

int main() {
    int tableau[100];

    // Correction : on utilise 100 car sizeof(tableau) renvoie 400 (taille en octets)
    for (int compteur = 0; compteur < 100; compteur++) {
        tableau[compteur] = compteur * 2;
    }

    printf("Programme termine avec succes : le tableau est rempli.\n");
    return (0);
}
