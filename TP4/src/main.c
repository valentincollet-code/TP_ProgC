#include <stdio.h>
#include "operator.h"
#include "fichier.h"
#include "liste.h"

// Prototypes des fonctions d'entrée pour chaque exercice
void exercice4_1();
void exercice4_2();
void exercice4_7();

int main() {
    int choix;

    printf("=== Menu de selection ===\n");
    printf("1. Exercice 4.1 (Operations de base)\n");
    printf("2. Exercice 4.2 (Gestion de fichiers)\n");
    printf("3. Exercice 4.7 (Operations Bitwise)\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch(choix) {
        case 1: exercice4_1(); break;
        case 2: exercice4_2(); break;
        case 3: exercice4_7(); break;
        default: printf("Choix invalide.\n");
    }

    return 0;
}

// --- ENTREE EXERCICE 4.1 ---
void exercice4_1() {
    int n1, n2, res;
    char op;
    printf("\n[Ex 4.1] Operateur (+, -, *, /, %%, &, |, ~) : ");
    scanf(" %c", &op);

    printf("Nombre 1 : ");
    scanf("%d", &n1);

    if (op != '~') {
        printf("Nombre 2 : ");
        scanf("%d", &n2);
    }

    switch(op) {
        case '+': res = somme(n1, n2); break;
        case '-': res = difference(n1, n2); break;
        case '*': res = produit(n1, n2); break;
        case '/': res = quotient(n1, n2); break;
        case '%': res = modulo(n1, n2); break;
        case '&': res = et_logique(n1, n2); break;
        case '|': res = ou_logique(n1, n2); break;
        case '~': res = negation(n1); break; // Correction : 1 seul argument !
        default: printf("Operateur inconnu.\n"); return;
    }
    printf("Resultat : %d\n", res);
}

// --- ENTREE EXERCICE 4.2 ---
void exercice4_2() {
    int choix;
    char nom_de_fichier[100];
    char message[256];

    printf("Que souhaitez-vous faire ?\n");
    printf("1. Lire un fichier\n");
    printf("2. Ecrire dans un fichier\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("\nEntrez le nom du fichier a lire : ");
        scanf("%s", nom_de_fichier);
        lire_fichier(nom_de_fichier); // Appelle ta fonction de fichier.c
    }
    else if (choix == 2) {
        printf("\nEntrez le nom du fichier dans lequel vous souhaitez ecrire : ");
        scanf("%s", nom_de_fichier);

        printf("Entrez le message a ecrire : ");
        getchar(); // Nettoyage indispensable du buffer
        fgets(message, sizeof(message), stdin); // Saisie du message

        ecrire_dans_fichier(nom_de_fichier, message); // Appelle ta fonction
    }
}
// --- ENTREE EXERCICE 4.7 ---
void exercice4_7() {
    liste_couleurs ma_liste;
    init_liste(&ma_liste);

    // Exemple de couleurs comme demandé dans l'énoncé
    couleur couleur1 = {0xFF, 0x00, 0x00, 0xFF}; // Rouge
    couleur couleur2 = {0x00, 0xFF, 0x00, 0xFF}; // Vert

    insertion(&couleur1, &ma_liste);
    insertion(&couleur2, &ma_liste);

    printf("\nListe des couleurs :\n");
    parcours(&ma_liste);
}
