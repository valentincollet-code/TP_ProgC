#include <stdio.h>
#include <math.h>

int main() {
    // Déclaration des variables
    double rayon, aire, perimetre;

    // Initialisation du rayon (tu peux changer cette valeur)
    rayon = 50;

    // Calculs
    // On utilise M_PI défini dans la bibliothèque math.h
    aire = M_PI * rayon * rayon;
    perimetre = 2 * M_PI * rayon;

    // Affichage des résultats
    // %.2f permet d'afficher 2 chiffres après la virgule
    printf("Pour un cercle de rayon %.2f :\n", rayon);
    printf("L'aire est de : %.2f\n", aire);
    printf("Le perimetre est de : %.2f\n", perimetre);

    return 0;
}
