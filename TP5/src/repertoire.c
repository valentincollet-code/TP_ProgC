#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "repertoire.h"

// Implémentation de la fonction demandée
void lire_dossier(char *nom_repertoire) {
    // 1. Ouvrir le flux du répertoire
    DIR *rep = opendir(nom_repertoire);

    if (rep == NULL) {
        perror("Erreur lors de l'ouverture du dossier");
        return;
    }

    struct dirent *entree;
    printf("Contenu de '%s' :\n", nom_repertoire);

    // 2. Parcourir et afficher chaque élément
    while ((entree = readdir(rep)) != NULL) {
        printf("  -> %s\n", entree->d_name);
    }

    // 3. Fermer le flux
    closedir(rep);
}

// Version itérative avec gestion de la pile
void lire_dossier_iteratif(char *nom_depart) {
    char dossiers[100][1024];
    int index = 0;

    strcpy(dossiers[index++], nom_depart);

    while (index > 0) {
        char courant[1024];
        strcpy(courant, dossiers[--index]);

        DIR *rep = opendir(courant);
        if (rep == NULL) continue;

        struct dirent *lecture;
        while ((lecture = readdir(rep)) != NULL) {
            // Ignorer les dossiers spéciaux pour éviter les boucles
            if (strcmp(lecture->d_name, ".") == 0 || strcmp(lecture->d_name, "..") == 0)
                continue;

            printf("%s/%s\n", courant, lecture->d_name);

            // Si c'est un répertoire (DT_DIR), on l'ajoute à la liste à visiter
            if (lecture->d_type == DT_DIR) {
                if (index < 100) { // Sécurité pour ne pas déborder du tableau
                    sprintf(dossiers[index++], "%s/%s", courant, lecture->d_name);
                }
            }
        }
        closedir(rep);
    }
}