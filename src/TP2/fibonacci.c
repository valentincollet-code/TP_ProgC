#include <stdio.h>

int main() {
    int n = 7; // On veut afficher jusqu'à U7
    int u0 = 0;
    int u1 = 1;
    int suivant;

    printf("Suite de Fibonacci jusqu'à U%d : ", n);

    for (int i = 0; i <= n; i++) {
        if (i == 0) {
            printf("%d", u0);
        } else if (i == 1) {
            printf(", %d", u1);
        } else {
            // Formule : Un = Un-1 + Un-2
            suivant = u0 + u1;
            printf(", %d", suivant);
            
            // On décale nos variables pour le prochain tour
            u0 = u1;      // L'ancien U1 devient le nouveau U0
            u1 = suivant; // Le terme qu'on vient de calculer devient le nouveau U1
        }
    }
    printf("\n");

    return 0;
}
