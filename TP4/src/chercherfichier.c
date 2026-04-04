#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char nom_fichier[100];
    char phrase[255];
    char ligne[1024];
    int num_ligne = 0;

    // 1. Demander le nom du fichier
    printf("Entrez le nom du fichier dans lequel chercher : ");
    fflush(stdout); // Force l'affichage immédiat de la question
    scanf("%s", nom_fichier);
    vider_buffer();

    // 2. Demander la phrase à rechercher dans le fichier
    printf("Entrez la phrase que vous souhaitez rechercher : ");
    fgets(phrase, 255, stdin);
    fflush(stdout); // Force l'affichage immédiat de la question
    phrase[strcspn(phrase, "\n")] = 0; // Enlever le saut de ligne

    // 3. Ouvrir le fichier
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nom_fichier);
        return 1;
    }

    printf("\nRésultats de la recherche :\n");

    // 4. Parcourir le fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        num_ligne++;
        int occurrences = 0;
        char *ptr = ligne;

        // Compter combien de fois la phrase apparaît dans la ligne actuelle
        while ((ptr = strstr(ptr, phrase)) != NULL) {
            occurrences++;
            ptr += strlen(phrase); // Avancer le pointeur pour trouver la suivante
        }

        // 5. Afficher si trouvé
        if (occurrences > 0) {
            printf("Ligne %d, %d fois\n", num_ligne, occurrences);
        }
    }

    fclose(f);
    return 0;
}
