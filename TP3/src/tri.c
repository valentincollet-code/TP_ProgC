#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour échanger deux éléments (Le Swap)
void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction de Partition (Cœur de Quicksort)
int partition(int tableau[], int bas, int haut) {
    int pivot = tableau[haut]; // On choisit le dernier élément comme pivot
    int i = (bas - 1);         // Index du plus petit élément

    for (int j = bas; j <= haut - 1; j++) {
        // Si l'élément actuel est plus petit ou égal au pivot
        if (tableau[j] <= pivot) {
            i++; // Incrémenter l'index du plus petit élément
            echanger(&tableau[i], &tableau[j]);
        }
    }
    echanger(&tableau[i + 1], &tableau[haut]);
    return (i + 1);
}

// Fonction principale de Tri Rapide (Récursive)
void quickSort(int tableau[], int bas, int haut) {
    if (bas < haut) {
        // pi est l'index de partition, tableau[pi] est maintenant au bon endroit
        int pi = partition(tableau, bas, haut);

        // Trier séparément les éléments avant et après la partition
        quickSort(tableau, bas, pi - 1);
        quickSort(tableau, pi + 1, haut);
    }
}

int main() {
    int tableau[100];
    int i;

    srand(time(NULL));

    // 1. Remplissage et Affichage Non Trié
    printf("Tableau non trié :\n");
    for (i = 0; i < 100; i++) {
        tableau[i] = (rand() % 201) - 100; // Valeurs entre -100 et 100
        printf("%d ", tableau[i]);
    }
    printf("\n\n");

    // 2. Lancement du Tri Rapide
    // On lui passe le tableau, l'index de début (0) et de fin (99)
    quickSort(tableau, 0, 99);

    // 3. Affichage Trié (avec retour à la ligne pour y voir clair)
    printf("Tableau trié par ordre croissant :\n");
    for (i = 0; i < 100; i++) {
        printf("%d ", tableau[i]);
        if (i % 10 == 9) printf("\n"); // Retour à la ligne tous les 10 nombres
    }
    printf("\n");

    return 0;
}
