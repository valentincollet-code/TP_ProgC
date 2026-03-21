#include <stdio.h>

int main() {
    int tableau[100];
    int recherche, trouve = 0;
    int debut = 0, fin = 99, milieu;

    // 1. On remplit le tableau avec des nombres triés (obligatoire pour la dichotomie)
    printf("Tableau trie :\n");
    for (int i = 0; i < 100; i++) {
        tableau[i] = i * 3; // Exemple : 0, 3, 6, 9, 12...
        printf("%d ", tableau[i]);
    }

    // 2. Demander l'entier à chercher
    printf("\n\nEntrez l'entier que vous souhaitez chercher : ");
    scanf("%d", &recherche);

    // 3. Algorithme de recherche dichotomique
    // On divise la zone de recherche par 2 à chaque tour
    while (debut <= fin) {
        milieu = (debut + fin) / 2;

        if (tableau[milieu] == recherche) {
            trouve = 1;
            break;
        }
        else if (tableau[milieu] < recherche) {
            debut = milieu + 1; // On ignore la partie gauche
        }
        else {
            fin = milieu - 1; // On ignore la partie droite
        }
    }

    // 4. Affichage du résultat
    if (trouve) {
        printf("Resultat : entier present\n");
    } else {
        printf("Resultat : entier absent\n");
    }

    return 0;
}