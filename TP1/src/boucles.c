#include <stdio.h>

int main() {
    int compteur = 7; // Cette valeur peut-être modifié

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