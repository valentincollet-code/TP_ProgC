#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int tableau[100];
    int recherche, trouve = 0;

    // 1. Initialisation du tableau avec des nombres aléatoires (entre 0 et 100)
    srand(time(NULL)); // Pour avoir des nombres différents à chaque exécution
    printf("Tableau :\n");
    for (int i = 0; i < 100; i++) {
        tableau[i] = rand() % 101;
        printf("%d ", tableau[i]);
    }

    // 2. Demander l'entier à l'utilisateur
    printf("\n\nEntrez l'entier que vous souhaitez chercher : ");
    scanf("%d", &recherche);

    // 3. Logique de recherche (Recherche séquentielle)
    for (int i = 0; i < 100; i++) {
        if (tableau[i] == recherche) {
            trouve = 1; // On l'a trouvé !
            break;      // On peut arrêter la boucle
        }
    }

    // 4. Affichage du résultat (présent / absent)
    if (trouve) {
        printf("Résultat : entier présent\n");
    } else {
        printf("Résultat : entier absent\n");
    }

    return 0;
}