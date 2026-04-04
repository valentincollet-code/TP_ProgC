#include <stdio.h>
#include "repertoire.h"

int main(int argc, char *argv[]) {
    // Vérification : on attend le nom du programme + 1 argument
    if (argc != 2) {
        printf("Utilisation : %s <nom_du_repertoire>\n", argv[0]);
        return 1;
    }

    char *nom_cible = argv[1];

    printf("=== EXERCICE 5.1 : LISTE SIMPLE ===\n");
    lire_dossier(nom_cible);

    return 0;
}