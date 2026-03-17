#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int taille = 10;
    int tab_int[taille];
    float tab_float[taille];

    // Initialisation du générateur aléatoire
    srand(time(NULL));

    // Pointeurs pour le parcours
    int *p_int = tab_int;
    float *p_float = tab_float;

    // 1. Remplissage des tableaux avec des valeurs aléatoires
    for (int i = 0; i < taille; i++) {
        *(p_int + i) = rand() % 100;           // Entier entre 0 et 99
        *(p_float + i) = (float)(rand() % 100) / 10.0f; // Float aléatoire
    }

    // 2. Affichage AVANT multiplication
    printf("Tableau d'entiers (avant) : ");
    for (int i = 0; i < taille; i++) printf("%d ", *(p_int + i));
    
    printf("\nTableau de floats (avant) : ");
    for (int i = 0; i < taille; i++) printf("%.2f ", *(p_float + i));

    // 3. Multiplication par 3 si l'indice est divisible par 2 (0, 2, 4...)
    for (int i = 0; i < taille; i++) {
        if (i % 2 == 0) {
            *(p_int + i) *= 3;
            *(p_float + i) *= 3;
        }
    }

    // 4. Affichage APRÈS multiplication
    printf("\n\nTableau d'entiers (après * 3 sur indices pairs) : ");
    for (int i = 0; i < taille; i++) printf("%d ", *(p_int + i));

    printf("\nTableau de floats (après * 3 sur indices pairs) : ");
    for (int i = 0; i < taille; i++) printf("%.2f ", *(p_float + i));
    
    printf("\n");

    return 0;
}
