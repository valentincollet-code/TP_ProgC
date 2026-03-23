#include <stdio.h>
#include "repertoire.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Utilisation : %s <nom_du_repertoire>\n", argv[0]);
        return 1;
    }
    printf("--- Liste Récursive ---\n");
    lire_dossier_recursif(argv[1]);
    return 0;
}
