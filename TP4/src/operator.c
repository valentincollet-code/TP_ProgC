#include "operator.h"

int somme(int n1, int n2) { return n1 + n2; }
int difference(int n1, int n2) { return n1 - n2; }
int produit(int n1, int n2) { return n1 * n2; }
int quotient(int n1, int n2) { return (n2 != 0) ? n1 / n2 : 0; }
int modulo(int n1, int n2) { return (n2 != 0) ? n1 % n2 : 0; }
int et_logique(int n1, int n2) { return n1 & n2; }
int ou_logique(int n1, int n2) { return n1 | n2; }
int negation(int n1, int n2) {
    return ~n1; // L'opérateur tilde ~ fait l'inversion des bits en C
}
