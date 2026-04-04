#ifndef LISTE_H
#define LISTE_H

// 1. Définition de la couleur
typedef struct {
    unsigned char r, v, b, a;
} couleur;

// 2. Définition du maillon (doit être AVANT liste_couleurs)
struct maillon {
    couleur data;
    struct maillon *next;
};

// 3. Définition de la liste
typedef struct {
    struct maillon *premier;
} liste_couleurs;

// 4. Prototypes
void init_liste(liste_couleurs *l);
void insertion(couleur *c, liste_couleurs *l);
void parcours(liste_couleurs *l);

#endif