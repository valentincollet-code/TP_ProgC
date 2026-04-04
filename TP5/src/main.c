#include <stdio.h>
#include "repertoire.h"

int main(int argc, char *argv[]) {
    // Vérification de l'argument en ligne de commande
    if (argc != 2) {
        printf("Utilisation : %s <nom_du_repertoire>\n", argv[0]);
        return 1;
    }

    char *cible = argv[1];

    printf("--- AFFICHAGE SIMPLE (5.1) ---\n");
    lire_dossier(cible);

    printf("\n--- EXPLORATION RÉCURSIVE (5.2) ---\n");
    lire_dossier_recursif(cible);

    return 0;
}