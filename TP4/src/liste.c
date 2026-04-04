#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void init_liste(liste_couleurs *l) {
    l->premier = NULL;
}

void insertion(couleur *c, liste_couleurs *l) {
    struct maillon *nouveau = malloc(sizeof(struct maillon));
    if (nouveau != NULL) {
        nouveau->data = *c;
        nouveau->next = l->premier;
        l->premier = nouveau;
    }
}

void parcours(liste_couleurs *l) {
    struct maillon *actuel = l->premier;
    while (actuel != NULL) {
        printf("Couleur : R=%02X, V=%02X, B=%02X, A=%02X\n",
                actuel->data.r, actuel->data.v, actuel->data.b, actuel->data.a);
        actuel = actuel->next;
    }
}