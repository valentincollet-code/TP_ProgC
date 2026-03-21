#include <stdio.h>

int main() {
    int num1 = 14;
    int num2 = 4;
    char op = '/'; // type d'opérations modifiable: (+, -, *, /, %, &, |, ~)

    printf("Calcul : %d %c %d\n", num1, op, num2);

    switch (op) {
        case '+':
            printf("Resultat : %d\n", num1 + num2);
            break;
        case '-':
            printf("Resultat : %d\n", num1 - num2);
            break;
        case '*':
            printf("Resultat : %d\n", num1 * num2);
            break;
        case '/':
            if (num2 != 0)
                printf("Resultat : %d\n", num1 / num2);
            else
                printf("Erreur : Division par zero !\n");
            break;
        case '%':
            printf("Resultat (Modulo) : %d\n", num1 % num2);
            break;
        case '&':
            printf("Resultat (ET binaire) : %d\n", num1 & num2);
            break;
        case '|':
            printf("Resultat (OU binaire) : %d\n", num1 | num2);
            break;
        case '~':
            printf("Resultat (NON binaire de num1) : %d\n", ~num1);
            break;
        default:
            printf("Operateur inconnu !\n");
    }

    return 0;
}
