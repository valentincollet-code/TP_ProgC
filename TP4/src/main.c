#include <stdio.h>
#include "operator.h"

int main() {
    int n1, n2, resultat;
    char op;

    // 1. On demande d'abord l'opérateur
    printf("Choisissez l'operateur (+, -, *, /, %%, &, |, ~) :\n");
    scanf(" %c", &op);

    // 2. On demande au moins le premier nombre
    printf("Entrez num1 :\n");
    scanf("%d", &n1);

    // 3. On demande le deuxième nombre SEULEMENT si ce n'est pas une négation
    if (op != '~') {
        printf("Entrez num2 :\n");
        scanf("%d", &n2);
    } else {
        n2 = 0; // On initialise n2 à 0 par sécurité, même s'il ne servira pas
    }

    // 4. Le switch reste le même
    switch(op) {
        case '+': resultat = somme(n1, n2); break;
        case '-': resultat = difference(n1, n2); break;
        case '*': resultat = produit(n1, n2); break;
        case '/': resultat = quotient(n1, n2); break;
        case '%': resultat = modulo(n1, n2); break;
        case '&': resultat = et_logique(n1, n2); break;
        case '|': resultat = ou_logique(n1, n2); break;
        case '~': resultat = negation(n1, n2); break;
        default:
            printf("Erreur : Operateur inconnu.\n");
            return 1;
    }

    printf("Resultat : %d\n", resultat);

    return 0;
}
