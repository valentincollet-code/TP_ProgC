#include <stdio.h>

int main() {
    int somme = 0;

    // 1. Boucle de 1 à 1000
    for (int i = 1; i <= 1000; i++) {
        
        // 2. Condition: nombre divisible par 11 (Prioritaire)
        if (i % 11 == 0) {
            // On utilise continue pour passer directement au nombre suivant
            continue;
        }

        // 3. Condition: nombre divisible par 5 ou par 7
        if (i % 5 == 0 || i % 7 == 0) {
            somme += i; // Équivalent à somme = somme + i
        }

        // 4. Vérification du dépassement de 5000
        if (somme > 5000) {
            printf("La somme a dépasse 5000 à l'index : %d\n", i);
            // On utilise break pour arrêter immédiatement la boucle
            break;
        }
    }

    // 5. Affichage de la somme finale
    printf("La somme finale est : %d\n", somme);

    return 0;
}
