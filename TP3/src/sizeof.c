#include <stdio.h>

int main() {
    // Affichage des tailles pour les entiers et leurs pointeurs
    printf("La taille de int est : %zu octets\n", sizeof(int));
    printf("La taille de int* est : %zu octets\n", sizeof(int*));
    printf("La taille de int** est : %zu octets\n", sizeof(int**));

    // Affichage pour les pointeurs de caractères
    printf("La taille de char* est : %zu octets\n", sizeof(char*));
    printf("La taille de char** est : %zu octets\n", sizeof(char**));
    printf("La taille de char*** est : %zu octets\n", sizeof(char***));

    // Affichage pour les pointeurs de flottants
    printf("La taille de float* est : %zu octets\n", sizeof(float*));
    printf("La taille de float** est : %zu octets\n", sizeof(float**));
    printf("La taille de float*** est : %zu octets\n", sizeof(float***));

    return 0;
}





    

