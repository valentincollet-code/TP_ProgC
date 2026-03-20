#include <stdio.h>

int main() {
    int nb_etudiants = 5;

    // Tableaux de pointeurs pour les chaînes de caractères
    char *noms[] = {"Dupont", "Durand", "Petit", "Leroy", "Moreau"};
    char *prenoms[] = {"Jean", "Marie", "Luc", "Alice", "Thomas"};
    char *adresses[] = {"Paris", "Lyon", "Marseille", "Lille", "Bordeaux"};

    // Tableaux pour les notes
    float notes_prog[] = {15.5, 12.0, 18.0, 10.5, 14.0};
    float notes_os[] = {14.0, 11.5, 17.0, 13.0, 12.5};

    printf("Gestion des Données Étudiantes :\n");
    printf("--------------------------------\n");

    for (int i = 0; i < nb_etudiants; i++) {
        // Utilisation de l'arithmétique des pointeurs comme demandé :
        // *(noms + i) est équivalent à noms[i]
        printf("Étudiant n°%d :\n", i + 1);
        printf("  Nom : %s %s\n", *(prenoms + i), *(noms + i));
        printf("  Adresse : %s\n", *(adresses + i));
        printf("  Note Programmation : %.2f\n", *(notes_prog + i));
        printf("  Note Système d'exploitation : %.2f\n", *(notes_os + i));
        printf("--------------------------------\n");
    }

    return 0;
}
