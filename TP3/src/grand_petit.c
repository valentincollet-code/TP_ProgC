#include <stdio.h>
#include <stdlib.h> // Pour rand() et srand()
#include <time.h>   // Pour time()

int main() {
    int tableau[100];
    int grand, petit;

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Remplissage du tableau avec des valeurs entre 1 et 1000
    for (int i = 0; i < 100; i++) {
        tableau[i] = (rand() % 1000) + 1;
    }

    // On initialise grand et petit avec le premier élément du tableau
    grand = tableau[0];
    petit = tableau[0];

    // Boucle pour trouver le plus grand et le plus petit
    for (int i = 1; i < 100; i++) {
        if (tableau[i] > grand) {
            grand = tableau[i];
        }
        if (tableau[i] < petit) {
            petit = tableau[i];
        }
    }

    printf("Le numéro le plus grand est : %d\n", grand);
    printf("Le numéro le plus petit est : %d\n", petit);

    return 0;
}
