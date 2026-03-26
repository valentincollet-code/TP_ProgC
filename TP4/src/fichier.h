#ifndef FICHIER_H
#define FICHIER_H

/* * Prototype de la fonction pour lire un fichier.
 * Elle prend en paramètre le nom du fichier.
 */
void lire_fichier(const char *nom_de_fichier);

/* * Prototype de la fonction pour écrire dans un fichier.
 * Elle prend en paramètre le nom du fichier et le message à enregistrer.
 */
void ecrire_dans_fichier(const char *nom_de_fichier, const char *message);

#endif
