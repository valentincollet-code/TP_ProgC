#include <stdio.h>
#include <dirent.h>
#include "repertoire.h"

void lire_dossier(char *nom_repertoire) {
    struct dirent *lecture;
    DIR *rep = opendir(nom_repertoire);

    if (rep == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return;
    }

    while ((lecture = readdir(rep)) != NULL) {
        printf("%s\n", lecture->d_name);
    }

    closedir(rep);
}
