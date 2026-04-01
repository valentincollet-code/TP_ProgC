#include <stdio.h>
#include <string.h>
#include "fichier.h"

int main() {
    int choix;
    char nom_fichier[100];
    char message[255];

    printf("Que souhaitez-vous faire ?\n");
    printf("1. Lire un fichier\n");
    printf("2. Ecrire dans un fichier\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    
    // On nettoie le tampon (le \n reste après scanf) pour éviter des bugs avec fgets
    getchar(); 

    if (choix == 1) {
        printf("Entrez le nom du fichier a lire : ");
        scanf("%s", nom_fichier);
        lire_fichier(nom_fichier);
    } 
    else if (choix == 2) {
        printf("Entrez le nom du fichier : ");
        scanf("%s", nom_fichier);
        
        getchar(); // Nettoyage du tampon à nouveau
        
        printf("Entrez votre message : ");
        // fgets permet de lire une phrase entière avec des espaces
        fgets(message, 255, stdin);
        
        // Supprime le saut de ligne ajouté par fgets à la fin du message
        message[strcspn(message, "\n")] = 0;
        
        ecrire_dans_fichier(nom_fichier, message);
    } 
    else {
        printf("Choix invalide.\n");
    }

    return 0;
}
