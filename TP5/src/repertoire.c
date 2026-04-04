#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "repertoire.h"

// --- Exercice 5.1 ---
void lire_dossier(char *nom_repertoire) {
    DIR *rep = opendir(nom_repertoire);
    if (rep == NULL) return;
    struct dirent *entree;
    while ((entree = readdir(rep)) != NULL) {
        printf("-> %s\n", entree->d_name);
    }
    closedir(rep);
}

// --- Exercice 5.2 ---
void lire_dossier_recursif(char *nom_repertoire) {
    DIR *rep = opendir(nom_repertoire);
    if (rep == NULL) return;
    struct dirent *entree;
    while ((entree = readdir(rep)) != NULL) {
        if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) continue;
        char chemin[1024];
        snprintf(chemin, sizeof(chemin), "%s/%s", nom_repertoire, entree->d_name);
        printf("%s\n", chemin);
        if (entree->d_type == DT_DIR) lire_dossier_recursif(chemin);
    }
    closedir(rep);
}

// --- Exercice 5.3 ---
void lire_dossier_iteratif(char *nom_repertoire) {
    char pile[100][1024];
    int top = 0;
    strncpy(pile[top++], nom_repertoire, 1024);
    while (top > 0) {
        char courant[1024];
        strncpy(courant, pile[--top], 1024);
        DIR *rep = opendir(courant);
        if (rep == NULL) continue;
        struct dirent *entree;
        while ((entree = readdir(rep)) != NULL) {
            if (strcmp(entree->d_name, ".") == 0 || strcmp(entree->d_name, "..") == 0) continue;
            char nouveau[1024];
            snprintf(nouveau, sizeof(nouveau), "%.500s/%.500s", courant, entree->d_name);
            printf("%s\n", nouveau);
            if (entree->d_type == DT_DIR && top < 100) strncpy(pile[top++], nouveau, 1024);
        }
        closedir(rep);
    }
}