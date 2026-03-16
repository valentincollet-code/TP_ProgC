#include <stdio.h>

int main() {
    // 1. Déclaration et affectation
    char c = 'A';
    unsigned char uc = 200;

    short s = -10;
    unsigned short us = 500;

    int i = -1000;
    unsigned int ui = 40000;

    long int li = -123456789L;
    unsigned long int uli = 123456789UL;

    long long int lli = -9223372036854775807LL;
    unsigned long long int ulli = 18446744073709551615ULL;

    float f = 3.14f;
    double d = 2.718281828;
    long double ld = 1.234567890123456789L;

    // 2. Affichage
    printf("--- Variables Entieres ---\n");
    printf("char : %c (valeur numerique: %d)\n", c, c);
    printf("unsigned char : %u\n", uc);
    printf("short : %d\n", s);
    printf("unsigned short : %u\n", us);
    printf("int : %d\n", i);
    printf("unsigned int : %u\n", ui);
    printf("long int : %ld\n", li);
    printf("unsigned long int : %lu\n", uli);
    printf("long long int : %lld\n", lli);
    printf("unsigned long long int : %llu\n", ulli);

    printf("\n--- Variables Flottantes ---\n");
    printf("float : %.2f\n", f);
    printf("double : %.10f\n", d);
    printf("long double : %.15Lf\n", ld);

    return 0;
}
