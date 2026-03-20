#include <stdio.h>

int main() {
    int n = 5; // Hauteur de la pyramide
    int i, j;

    for (i = 1; i <= n; i++) {
        // 1. Boucle pour les espaces (centrage)
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // 2. Boucle pour les nombres croissants (de 1 à i)
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }

        // 3. Boucle pour les nombres décroissants (de i-1 à 1)
        for (j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }

        // Passage à la ligne suivante
        printf("\n");
    }

    printf("\nLa génération de la pyramide est terminée.\n");

    return 0;
}
