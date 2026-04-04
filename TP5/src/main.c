#include <stdio.h>
#include "repertoire.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage : %s <nom_du_repertoire>\n", argv[0]);
        return 1;
    }

    printf("\n--- SIMPLE (5.1) ---\n");
    lire_dossier(argv[1]);

    printf("\n--- RECURSIF (5.2) ---\n");
    lire_dossier_recursif(argv[1]);

    printf("\n--- ITERATIF (5.3) ---\n");
    lire_dossier_iteratif(argv[1]);

    return 0;
}