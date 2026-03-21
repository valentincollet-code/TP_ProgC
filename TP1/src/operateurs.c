#include <stdio.h>

int main() {
    // Initialisation des variables (on peut modifier les variables)
    int a = 39;
    int b = 435;

    printf("Valeurs : a = %d, b = %d\n\n", a, b);

    // 1. Addition
    printf("Addition (a + b) : %d\n", a + b);

    // 2. Soustraction
    printf("Soustraction (a - b) : %d\n", a - b);

    // 3. Multiplication
    printf("Multiplication (a * b) : %d\n", a * b);

    // 4. Division (Attention : division entiere ici)
    printf("Division (a / b) : %d\n", a / b);

    // 5. Modulo (Le reste de la division)
    printf("Modulo (a %% b) : %d\n", a % b);

    // 6. Comparaison d'egalite (==)
    // On affiche le resultat sous forme d'entier (0 ou 1)
    printf("Est egal (a == b) : %d\n", a == b);

    // 7. Comparaison de superiorite (>)
    printf("Est superieur (a > b) : %d\n", a > b);

    return 0;
}
