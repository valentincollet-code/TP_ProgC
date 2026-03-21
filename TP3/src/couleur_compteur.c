#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. Définition de la structure pour une couleur (RGBA)
typedef struct {
    unsigned char r, g, b, a;
} Couleur;

// 2. Structure pour stocker une couleur et son nombre d'apparitions
typedef struct {
    Couleur couleur;
    int compteur;
} CouleurCompte;

// Fonction pour comparer deux couleurs
int sont_identiques(Couleur c1, Couleur c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}

int main() {
    Couleur tableau[100];
    CouleurCompte distinctes[100];
    int nb_distinctes = 0;

    srand(time(NULL));

    // 3. Remplissage du tableau avec des couleurs aléatoires
    // On limite à 0-2 pour forcer des doublons et tester le compteur
    for (int i = 0; i < 100; i++) {
        tableau[i].r = rand() % 3;
        tableau[i].g = rand() % 3;
        tableau[i].b = rand() % 3;
        tableau[i].a = 255; // ff en hexadécimal
    }

    // 4. Logique de comptage
    for (int i = 0; i < 100; i++) {
        int index_trouve = -1;

        for (int j = 0; j < nb_distinctes; j++) {
            if (sont_identiques(tableau[i], distinctes[j].couleur)) {
                index_trouve = j;
                break;
            }
        }

        if (index_trouve != -1) {
            distinctes[index_trouve].compteur++;
        } else {
            distinctes[nb_distinctes].couleur = tableau[i];
            distinctes[nb_distinctes].compteur = 1;
            nb_distinctes++;
        }
    }

    // 5. Affichage final au format de l'énoncé
    printf("Couleurs distinctes trouvees :\n");
    for (int i = 0; i < nb_distinctes; i++) {
        // Format : ff 0x23 0x23 0x45 : 2
        printf("%02x 0x%02x 0x%02x 0x%02x : %d\n",
               distinctes[i].couleur.a, // On affiche souvent A en premier dans cet exercice
               distinctes[i].couleur.r,
               distinctes[i].couleur.g,
               distinctes[i].couleur.b,
               distinctes[i].compteur);
    }

    return 0;
}