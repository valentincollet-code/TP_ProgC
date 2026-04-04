#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "repertoire.h"

// --- Exercice 5.1 : Lecture simple ---
void lire_dossier(char *nom_repertoire) {
    DIR *rep = opendir(nom_repertoire);
    if (rep == NULL) {
        perror("Erreur opendir");
        return;
    }

    struct dirent *entree;
    while ((entree = readdir(rep)) != NULL) {
        printf("-> %s\n", entree->d_name);
    }
    closedir(rep);
}

// --- Exercice 5.2 : Lecture récursive ---
void lire_dossier_recursif(char *nom_repertoire) {
    DIR *rep = opendir(nom_repertoire);
    if (rep == NULL) return;

    struct dirent *entree;
    while ((entree = readdir(rep)) != NULL) {
        // Ignorer les dossiers spéciaux "." et ".."
        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) {
            continue;
        }

        // Construction du chemin complet
        char chemin[1024];
        snprintf(chemin, sizeof(chemin), "%s/%s", nom_repertoire, entree->d_name);

        // Affichage du chemin courant
        printf("%s\n", chemin);

        // Si c'est un dossier, on appelle la fonction récursivement
        if (entree->d_type == DT_DIR) {
            lire_dossier_recursif(chemin);
        }
    }
    closedir(rep);
}

// --- Version itérative  ---
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
            if (strcmp(lecture->d_name, ".") == 0 || strcmp(lecture->d_name, "..") == 0)
                continue;
            printf("%s/%s\n", courant, lecture->d_name);
            if (lecture->d_type == DT_DIR && index < 100) {
                sprintf(dossiers[index++], "%s/%s", courant, lecture->d_name);
            }
        }
        closedir(rep);
    }
}