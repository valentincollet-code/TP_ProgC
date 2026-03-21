#include <stdio.h>

int main() {
    int nombres[] = {0, 4096, 65536, 65535, 1024};
    int taille = 5;

    for (int n = 0; n < taille; n++) {
        int num = nombres[n];
        printf("Nombre %d en binaire : ", num);

        // Si le nombre est 0, on l'affiche simplement
        if (num == 0) {
            printf("0");
        } else {
            // Parcourir les bits du plus significatif au moins significatif
            // On commence à 31 car un int fait 32 bits (4 octets)
            int a_commence = 0;
            for (int i = 31; i >= 0; i--) {
                int bit = (num >> i) & 1;
                
                // Pour ne pas afficher tous les 0 inutiles au début
                if (bit == 1) a_commence = 1;
                
                if (a_commence) {
                    printf("%d", bit);
                }
            }
        }
        printf("\n");
    }

    return 0;
}
