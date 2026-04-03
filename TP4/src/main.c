#include <stdio.h>
#include "operator.h"

// Prototypes des fonctions d'entrée pour chaque exercice
void exercice4_1();
void exercice4_2();
void exercice4_7();

int main() {
    int choix;

    printf("=== Menu de selection ===\n");
    printf("1. Exercice 4.1 (Operations de base)\n");
    printf("2. Exercice 4.2 (Carre et Cube)\n");
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
    int n, res;
    char choix;
    printf("\n[Ex 4.2] Calculer (c)arre ou (u)be ? ");
    scanf(" %c", &choix);
    printf("Nombre : ");
    scanf("%d", &n);

    if (choix == 'c') res = carre(n);
    else if (choix == 'u') res = cube(n);
    else { printf("Choix invalide.\n"); return; }

    printf("Resultat : %d\n", res);
}

// --- ENTREE EXERCICE 4.7 ---
void exercice4_7() {
    // Ici tu mettras la logique pour les shifts (<<, >>) et XOR (^)
    printf("\n[Ex 4.7] Logique bitwise avancee (a implementer).\n");
}