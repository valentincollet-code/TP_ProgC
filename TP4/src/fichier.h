#ifndef FICHIER_H
#define FICHIER_H

/**
 * Lit le contenu d'un fichier et l'affiche sur la console.
 * @param nom_de_fichier Le chemin/nom du fichier à ouvrir.
 */
void lire_fichier(const char *nom_de_fichier);

/**
 * Crée ou écrase un fichier avec un nouveau message.
 * @param nom_de_fichier Le chemin/nom du fichier.
 * @param message Le texte à enregistrer.
 */
void ecrire_dans_fichier(const char *nom_de_fichier, const char *message);

/**
 * Ajoute un message à la fin d'un fichier existant sans l'effacer (Exercice 4.3).
 * @param nom_de_fichier Le chemin/nom du fichier.
 * @param message Le texte à ajouter.
 */
void ajouter_dans_fichier(const char *nom_de_fichier, const char *message);

#endif