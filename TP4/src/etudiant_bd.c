#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fichier.h"

typedef struct {
    char nom[50];
    char prenom[50];
    char adresse[100];
    int note1;
    int note2;
} Etudiant;

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Etudiant promo[5];
    char ligne[300];

    for (int i = 0; i < 5; i++) {
        printf("--- Étudiant %d ---\n", i + 1);
        
        printf("Nom : ");
        fgets(promo[i].nom, 50, stdin);
        promo[i].nom[strcspn(promo[i].nom, "\n")] = 0;

        printf("Prénom : ");
        fgets(promo[i].prenom, 50, stdin);
        promo[i].prenom[strcspn(promo[i].prenom, "\n")] = 0;

        printf("Adresse : ");
        fgets(promo[i].adresse, 100, stdin);
        promo[i].adresse[strcspn(promo[i].adresse, "\n")] = 0;

        printf("Note 1 : ");
        if (scanf("%d", &promo[i].note1) != 1) promo[i].note1 = 0;
        printf("Note 2 : ");
        if (scanf("%d", &promo[i].note2) != 1) promo[i].note2 = 0;
        vider_buffer(); 
        
        printf("\n");

        sprintf(ligne, "Nom: %s | Prenom: %s | Adresse: %s | Notes: %d, %d", 
                promo[i].nom, promo[i].prenom, promo[i].adresse, promo[i].note1, promo[i].note2);
        
        ajouter_dans_fichier("etudiant.txt", ligne);
    }

    printf("Terminé ! Les 5 étudiants sont enregistrés dans etudiant.txt\n");
    return 0;
}
