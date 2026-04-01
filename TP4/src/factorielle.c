#include <stdio.h>

// Définition de la fonction factorielle (Récursive)
int factorielle(int num) {
    if (num == 0) {
        printf("fact(0): 1\n");
        return 1;
    } else {
        int valeur = num * factorielle(num - 1);
        printf("fact(%d): %d\n", num, valeur);
        return (valeur);
    }
}

int main() {
    int n;

    printf("Entrez un nombre entier naturel : ");
    if (scanf("%d", &n) != 1) {
        printf("Erreur de saisie.\n");
        return 1;
    }

    if (n < 0) {
        printf("La factorielle n'est pas définie pour les nombres négatifs.\n");
    } else {
        int resultat = factorielle(n);
        printf("\nLe résultat final de %d! est : %d\n", n, resultat);
    }

    return 0;
}
