#include <stdio.h>

int main() {
    int nb_etudiants = 5;

    // Tableaux de pointeurs pour les chaînes de caractères
    char *noms[] = {"Collet", "Bouveret", "Dia", "Titiana", "DECOOPMAN"};
    char *prenoms[] = {"Valentin", "Clément", "Demba", "Janette", "Sandy"};
    char *adresses[] = {"Savigny sur Orge", "Saint Maure", "Paris", "Lieusaint", "Melun"};

    // Tableaux pour les notes
    float notes_prog[] = {16, 20, 18.0, 19, 14.0};
    float notes_os[] = {18, 20, 17.0, 18, 17};

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
