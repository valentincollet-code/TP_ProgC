#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

// Fonction pour lire et afficher le contenu d'un fichier
void lire_fichier(const char *nom_de_fichier) {
    FILE *f = fopen(nom_de_fichier, "r"); // "r" pour read (lecture)
    
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier '%s'.\n", nom_de_fichier);
        return;
    }

    char ligne[255];
    printf("Contenu du fichier %s :\n", nom_de_fichier);
    while (fgets(ligne, 255, f) != NULL) {
        printf("%s", ligne);
    }
    
    fclose(f); // Toujours fermer le fichier après usage
}

// Fonction pour ecrire un message dans un fichier
void ecrire_dans_fichier(const char *nom_de_fichier, const char *message) {
    FILE *f = fopen(nom_de_fichier, "w"); // "w" pour write (ecriture/ecrasement)
    
    if (f == NULL) {
        printf("Erreur : Impossible de creer le fichier '%s'.\n", nom_de_fichier);
        return;
    }

    fprintf(f, "%s", message);
    fclose(f);
    printf("Message enregistre avec succes dans %s.\n", nom_de_fichier);
}
