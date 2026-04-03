#include <stdio.h>

int main() {
    char s1[] = "Buenos dias";
    char s2[] = " Mundo !";
    char copie[50];      // Un espace vide pour la copie
    char concat[100];    // Un espace assez grand pour s1 + s2

    // --- 1. Calculer la longueur de s1 ---
    int longueur = 0;
    while (s1[longueur] != '\0') {
        longueur++;
    }
    printf("Longueur de s1 : %d\n", longueur);

    // --- 2. Copier s1 dans 'copie' ---
    int i = 0;
    while (s1[i] != '\0') {
        copie[i] = s1[i];
        i++;
    }
    copie[i] = '\0'; // IMPORTANT : ne pas oublier de fermer la chaîne !
    printf("Copie de s1 : %s\n", copie);

    // --- 3. Concaténer s1 et s2 dans 'concat' ---
    int j = 0;
    // D'abord on copie s1
    while (s1[j] != '\0') {
        concat[j] = s1[j];
        j++;
    }
    // Ensuite on ajoute s2 à la suite
    int k = 0;
    while (s2[k] != '\0') {
        concat[j] = s2[k];
        j++;
        k++;
    }
    concat[j] = '\0'; // On ferme la chaîne finale
    printf("Résultat concaténé : %s\n", concat);

    return 0;
}
