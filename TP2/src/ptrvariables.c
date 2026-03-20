#include <stdio.h>

int main() {
    // 1. Déclaration des variables de base
    int i = 0x1234;
    float f = 2.5f;

    // 2. Déclaration des pointeurs pour stocker les adresses
    int *ptr_i = &i;
    float *ptr_f = &f;

    // 3. Affichage AVANT manipulation
    printf("Avant la manipulation :\n");
    printf("Adresse de i : %p, Valeur de i : %x\n", (void*)ptr_i, i);
    printf("Adresse de f : %p, Valeur de f : %x\n", (void*)ptr_f, *(unsigned int*)&f);

    // 4. Manipulation via les pointeurs
    *ptr_i = 0xABCD; // On change la valeur de i en passant par son adresse
    *ptr_f = 5.5f;   // On change la valeur de f en passant par son adresse

    printf("\nAprès la manipulation :\n");
    
    // 5. Affichage APRÈS manipulation
    printf("Adresse de i : %p, Valeur de i : %x\n", (void*)ptr_i, i);
    printf("Adresse de f : %p, Valeur de f : %x\n", (void*)ptr_f, *(unsigned int*)&f);

    return 0;
}
