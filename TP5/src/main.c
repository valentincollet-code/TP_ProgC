#include <stdio.h>
#include "repertoire.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Utilisation : %s <nom_du_repertoire>\n", argv[0]);
        return 1;
    }
    printf("--- Liste Itérative ---\n");
    lire_dossier_iteratif(argv[1]);
    return 0;
}
