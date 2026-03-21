
#include <stdio.h>

// 1. Définition de la structure
typedef struct {
    unsigned char r; // Rouge
    unsigned char g; // Vert
    unsigned char b; // Bleu
    unsigned char a; // Alpha
} Couleur;

int main() {
    // 2. Création d'un tableau de 10 éléments de type Couleur
    Couleur tableau[10];

    // 3. Initialisation des couleurs avec des valeurs hexadécimales
    // Exemple : Rouge = 0xef (239), Vert = 0x78 (120), Bleu = 0x12 (18), Alpha = 0xff (255)
    for (int i = 0; i < 10; i++) {
        tableau[i].r = 0xef;
        tableau[i].g = 0x78;
        tableau[i].b = 0x12;
        tableau[i].a = 0xff;
    }

    // On peut changer la deuxième couleur pour tester (comme dans l'exemple)
    tableau[1].r = 44;  // 0x2c
    tableau[1].g = 200; // 0xc8
    tableau[1].b = 100; // 0x64
    tableau[1].a = 255; // 0xff

    // 4. Affichage des détails
    for (int i = 0; i < 10; i++) {
        printf("Couleur %d :\n", i + 1);
        printf("Rouge : %d\n", tableau[i].r);
        printf("Vert  : %d\n", tableau[i].g);
        printf("Bleu  : %d\n", tableau[i].b);
        printf("Alpha : %d\n\n", tableau[i].a);
    }

    return 0;
}//