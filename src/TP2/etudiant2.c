#include <stdio.h>
#include <string.h>

// Définition de la structure
struct Etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float note_prog;
    float note_os;
};

int main() {
    // Création d'un tableau de 5 structures Etudiant
    struct Etudiant classe[5];

    // Initialisation du premier étudiant avec strcpy
    strcpy(classe[0].nom, "Dupont");
    strcpy(classe[0].prenom, "Marie");
    strcpy(classe[0].adresse, "20, Boulevard Niels Bohr, Lyon");
    classe[0].note_prog = 16.5;
    classe[0].note_os = 12.1;

    // Ajout d'un deuxième étudiant pour l'exemple
    strcpy(classe[1].nom, "Martin");
    strcpy(classe[1].prenom, "Pierre");
    strcpy(classe[1].adresse, "22, Boulevard Niels Bohr, Lyon");
    classe[1].note_prog = 14.0;
    classe[1].note_os = 14.1;

    // (Tu peux remplir les 3 autres de la même manière...)

    // Affichage
    for (int i = 0; i < 2; i++) { // On affiche les 2 remplis
        printf("Étudiant.e %d :\n", i + 1);
        printf("Nom : %s\n", classe[i].nom);
        printf("Prénom : %s\n", classe[i].prenom);
        printf("Adresse : %s\n", classe[i].adresse);
        printf("Note 1 : %.1f\n", classe[i].note_prog);
        printf("Note 2 : %.1f\n\n", classe[i].note_os);
    }

    return 0;
}
