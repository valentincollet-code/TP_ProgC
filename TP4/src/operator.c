#include "operator.h"

// --- Exercice 4.1 ---
int somme(int num1, int num2) {
    return num1 + num2;
}

int difference(int num1, int num2) {
    return num1 - num2;
}

int produit(int num1, int num2) {
    return num1 * num2;
}

int quotient(int num1, int num2) {
    if (num2 != 0) return num1 / num2;
    return 0; // Sécurité division par zéro
}

int modulo(int num1, int num2) {
    if (num2 != 0) return num1 % num2;
    return 0;
}

int et_logique(int num1, int num2) {
    return num1 & num2;
}

int ou_logique(int num1, int num2) {
    return num1 | num2;
}

int negation(int num1) {
    return ~num1;
}

// --- Exercice 4.2 ---
int carre(int n) {
    return n * n;
}

int cube(int n) {
    return n * n * n;
}