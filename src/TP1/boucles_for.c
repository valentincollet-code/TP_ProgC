#include <stdio.h>

int main() {
    int compteur = 5; // Tu peux changer cette valeur (doit être < 10)
    
    for (int i = 1; i <= compteur; i++) {
        for (int j = 1; j <= i; j++) {
            // Si on est sur les bords du triangle ou à la dernière ligne
            if (j == 1 || j == i || i == compteur) {
                printf("* ");
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }
    return 0;
}
