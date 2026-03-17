#include <stdio.h>

int main() {
    // On utilise un 'unsigned int' pour éviter les problèmes de signe avec les décalages
    unsigned int d = 2147483648; // Exemple de valeur (ici seul le bit 31 est à 1)

    /* En C, on compte souvent de droite à gauche (0 à 31).
       Si on parle du 4ème bit en partant de la gauche (bit 28) 
       et du 20ème en partant de la gauche (bit 12).
    */

    // Extraction du 4ème bit de gauche (index 28)
    int bit4 = (d >> 28) & 1;

    // Extraction du 20ème bit de gauche (index 12)
    int bit20 = (d >> 12) & 1;

    // Vérification : si les deux sont à 1
    if (bit4 == 1 && bit20 == 1) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}
