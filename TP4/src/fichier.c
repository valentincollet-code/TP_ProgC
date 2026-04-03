#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

void lire_fichier(const char *nom_de_fichier) {
    FILE *f = fopen(nom_de_fichier, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier '%s'.\n", nom_de_fichier);
        return;
    }

    char ligne[256]; // Un peu plus large
    printf("Contenu du fichier %s :\n", nom_de_fichier);
    // Utilisation de sizeof (plus secure que 255)
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        printf("%s", ligne);
    }
    printf("\n");

    fclose(f);
}

void ecrire_dans_fichier(const char *nom_de_fichier, const char *message) {
    FILE *f = fopen(nom_de_fichier, "w");
    if (f == NULL) {
        printf("Erreur : Impossible de creer le fichier '%s'.\n", nom_de_fichier);
        return;
    }

    // On utilise fputs ou fprintf, les deux fonctionnent
    fputs(message, f);
    fclose(f);
    printf("Message enregistre avec succes dans %s.\n", nom_de_fichier);
}

void ajouter_dans_fichier(const char *nom_de_fichier, const char *message) {
    FILE *f = fopen(nom_de_fichier, "a");
    if (f == NULL) {
        printf("Erreur d'ajout dans %s.\n", nom_de_fichier);
        return;
    }
    fputs(message, f);
    fclose(f);
}