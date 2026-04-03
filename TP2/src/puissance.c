#include <stdio.h>

int main() {
    // 1. Déclaration et initialisation des variables (a et b modifiable)
    int a = 8;         // La base
    int b = 9;         // L'exposant
    long resultat = 1; // On commence à 1 pour la multiplication

    // 2. Calcul de la puissance avec une boucle for
    // On multiplie 'resultat' par 'a', 'b' fois.
    for (int i = 0; i < b; i++) {
        resultat = resultat * a;
    }

    // 3. Affichage du résultat
    printf("%d élevé à la puissance %d est égal à : %ld\n", a, b, resultat);

    return 0;
}

