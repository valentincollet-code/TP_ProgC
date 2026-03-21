#include <stdio.h>

// Fonction utilitaire pour éviter de répéter le code
void afficher_octets(void *ptr, size_t taille) {
    unsigned char *p = (unsigned char *)ptr;
    for (size_t i = 0; i < taille; i++) {
        // %02x affiche en hexadécimal sur 2 caractères
        printf("%02x ", p[i]);
    }
    printf("\n\n");
}

int main() {
    // Déclaration des variables avec des valeurs arbitraires
    short s = 0x0203;
    int i = 0x01020304;
    long int li = 0x0102030405060708;
    float f = 1.0f;
    double d = 1.0;
    long double ld = 1.0L;

    printf("Octets de short :\n");
    afficher_octets(&s, sizeof(s));

    printf("Octets de int :\n");
    afficher_octets(&i, sizeof(i));

    printf("Octets de long int :\n");
    afficher_octets(&li, sizeof(li));

    printf("Octets de float :\n");
    afficher_octets(&f, sizeof(f));

    printf("Octets de double :\n");
    afficher_octets(&d, sizeof(d));

    printf("Octets de long double :\n");
    afficher_octets(&ld, sizeof(ld));

    return 0;
}