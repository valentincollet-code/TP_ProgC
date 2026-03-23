#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "repertoire.h"

void lire_dossier_recursif(char *nom_repertoire) {
    struct dirent *lecture;
    DIR *rep = opendir(nom_repertoire);
    char chemin[1024];

    if (rep == NULL) return;

    while ((lecture = readdir(rep)) != NULL) {
        // On ignore les répertoires "." et ".."
        if (strcmp(lecture->d_name, ".") == 0 || strcmp(lecture->d_name, "..") == 0) {
            continue;
        }

        printf("%s/%s\n", nom_repertoire, lecture->d_name);

        // Si c'est un répertoire (type DT_DIR), on appelle la fonction récursivement
        if (lecture->d_type == DT_DIR) {
            sprintf(chemin, "%s/%s", nom_repertoire, lecture->d_name);
            lire_dossier_recursif(chemin);
        }
    }
    closedir(rep);
}
