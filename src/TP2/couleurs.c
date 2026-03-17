#include <stdio.h>

// Définition de la structure RGBA
struct Couleur {
    unsigned char r; // Rouge
    unsigned char g; // Vert
    unsigned char b; // Bleu
    unsigned char a; // Alpha (transparence)
};

int main() {
    // Création d'un tableau de 10 structures Couleur
    struct Couleur palette[10];

    // Initialisation de la première couleur en hexadécimal
    palette[0].r = 0xef; // 239 en décimal
    palette[0].g = 0x78; // 120 en décimal
    palette[0].b = 0x12; // 18 en décimal
    palette[0].a = 0xff; // 255 en décimal

    // Initialisation d'une deuxième couleur pour l'exemple
    palette[1].r = 0x2c; // 44 en décimal
    palette[1].g = 0xc8; // 200 en décimal
    palette[1].b = 0x64; // 100 en décimal
    palette[1].a = 0xff;

    // Affichage des couleurs
    for (int i = 0; i < 2; i++) {
        printf("Couleur %d :\n", i + 1);
        printf("  Rouge : %u\n", palette[i].r);
        printf("  Vert  : %u\n", palette[i].g);
        printf("  Bleu  : %u\n", palette[i].b);
        printf("  Alpha : %u\n\n", palette[i].a);
    }

    return 0;
}
