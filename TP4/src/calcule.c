#include <stdio.h>
#include <stdlib.h>
#include "operator.h"

int main(int argc, char *argv[]) {
    // Vérification du nombre d'arguments
    if (argc != 4) {
        printf("Usage: %s <operateur> <nb1> <nb2>\n", argv[0]);
        return 1;
    }

    char op = argv[1][0];
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);
    int resultat = 0;

    switch (op) {
        case '+': resultat = num1 + num2; break;
        case '-': resultat = num1 - num2; break;
        case '*': resultat = num1 * num2; break;
        case '/': 
            if(num2 == 0) { printf("Division par zero !\n"); return 1; }
            resultat = num1 / num2; 
            break;
        case '%': resultat = num1 % num2; break;
        case '&': resultat = num1 & num2; break;
        case '|': resultat = num1 | num2; break;
        default:
            printf("Operateur inconnu\n");
            return 1;
    }

// Affichage résultats
    printf("Résultat : %d\n", resultat);
    return 0;
}
