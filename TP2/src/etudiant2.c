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
    strcpy(classe[0].nom, "COLLET");
    strcpy(classe[0].prenom, "Valentin");
    strcpy(classe[0].adresse, "2 rue des Abricotiers, Savigny-sur-Orge");
    classe[0].note_prog = 16;
    classe[0].note_os = 18;

    // Ajout étudiant 2
    strcpy(classe[1].nom, "Bouveret");
    strcpy(classe[1].prenom, "Clément");
    strcpy(classe[1].adresse, "Rue Albert, Saint-Maure");
    classe[1].note_prog = 20.0;
    classe[1].note_os = 19.0;

    // Ajout étudiant 3
    strcpy(classe[2].nom, "Dia");
    strcpy(classe[2].prenom, "Demba");
    strcpy(classe[2].adresse, "Rue Rivoli, Paris");
    classe[2].note_prog = 16.0;
    classe[2].note_os = 17.0;

    // Ajout étudiant 4
    strcpy(classe[3].nom, "Titiana");
    strcpy(classe[3].prenom, "Jeanette");
    strcpy(classe[3].adresse, "Rue Gaston, Lieusaint");
    classe[3].note_prog = 19.0;
    classe[3].note_os = 18.0;

    // Ajout étudiant 5
    strcpy(classe[4].nom, "Valadier");
    strcpy(classe[4].prenom, "Julien");
    strcpy(classe[4].adresse, "Avenue de l'ICAM, Paris");
    classe[4].note_prog = 19.0;
    classe[4].note_os = 19.0;


    // Affichage
    for (int i = 0; i < 5; i++) { // On affiche les 5 étudiants
        printf("Étudiant.e %d :\n", i + 1);
        printf("Nom : %s\n", classe[i].nom);
        printf("Prénom : %s\n", classe[i].prenom);
        printf("Adresse : %s\n", classe[i].adresse);
        printf("Note 1 : %.1f\n", classe[i].note_prog);
        printf("Note 2 : %.1f\n\n", classe[i].note_os);
    }

    return 0;
}
