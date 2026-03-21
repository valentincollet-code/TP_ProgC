//
// Created by valen on 21/03/2026.
//
#include <stdio.h>

int main() {
    // 1. Tableau de phrases (chaque phrase est un pointeur vers des caractères)
    char *phrases[10] = {
        "Bonjour, comment ca va ?",
        "Il fait beau aujourd'hui.",
        "Beaucoup d'exercice dans ce TP !.",
        "J'ai utilisé CLion.",
        "La procgrammation en C est intéressante.",
        "C'est le week-end.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."
    };

    // La phrase cible
    char *recherche = "Il fait beau aujourd'hui.";
    int trouve = 0;

    // 2. Boucle pour parcourir les 10 phrases
    for (int i = 0; i < 10; i++) {
        int j = 0;
        int match = 1;

        // 3. Comparaison manuelle caractère par caractère
        // On s'arrête dès qu'on voit une différence ou la fin de chaîne \0
        while (phrases[i][j] != '\0' || recherche[j] != '\0') {
            if (phrases[i][j] != recherche[j]) {
                match = 0; // Ce n'est pas la bonne phrase
                break;
            }
            j++;
        }

        if (match == 1) {
            trouve = 1;
            break;
        }
    }

    // 4. Résultat
    if (trouve) {
        printf("Phrase trouvee\n");
    } else {
        printf("Phrase non trouvee\n");
    }

    return 0;
}