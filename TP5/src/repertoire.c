#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "repertoire.h"

void lire_dossier_iteratif(char *nom_depart) {
    // On va utiliser un tableau de chaînes pour stocker les dossiers à visiter
    char dossiers[100][1024]; 
    int index = 0;
    
    strcpy(dossiers[index++], nom_depart);

    while (index > 0) {
        char courant[1024];
        strcpy(courant, dossiers[--index]); // On récupère le dernier dossier ajouté

        DIR *rep = opendir(courant);
        if (rep == NULL) continue;

        struct dirent *lecture;
        while ((lecture = readdir(rep)) != NULL) {
            if (strcmp(lecture->d_name, ".") == 0 || strcmp(lecture->d_name, "..") == 0)
                continue;

            printf("%s/%s\n", courant, lecture->d_name);

            // Si c'est un dossier, on l'ajoute à notre liste de tâches
            if (lecture->d_type == DT_DIR) {
                sprintf(dossiers[index++], "%s/%s", courant, lecture->d_name);
            }
        }
        closedir(rep);
    }
}
