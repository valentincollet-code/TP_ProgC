#include <stdio.h>

//Affiche la taille en octets des différents types de base
int main() {
    printf("--- Tailles des types de base (en octets) ---\n\n");

    // Types entiers avec versions signées et non-signées
    printf("char : %lu\n", sizeof(char));
    printf("unsigned char : %lu\n", sizeof(unsigned char));

    printf("short : %lu\n", sizeof(short));
    printf("unsigned short : %lu\n", sizeof(unsigned short));

    printf("int : %lu\n", sizeof(int));
    printf("unsigned int : %lu\n", sizeof(unsigned int));

    printf("long int : %lu\n", sizeof(long int));
    printf("unsigned long int : %lu\n", sizeof(unsigned long int));

    printf("long long int : %lu\n", sizeof(long long int));
    printf("unsigned long long int : %lu\n", sizeof(unsigned long long int));

    // Types flottants (pas de version signées/non signées)
    printf("\n--- Types flottants ---\n");
    printf("float : %lu\n", sizeof(float));
    printf("double : %lu\n", sizeof(double));
    printf("long double : %lu\n", sizeof(long double));

    return 0;
}
