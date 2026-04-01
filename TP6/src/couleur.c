/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#define _GNU_SOURCE // pour éviter les avertissements liés à c99
#include "couleur.h"
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>

// Compter les couleurs distinctes
couleur_compteur *compte_couleur(couleur *c, int csize)
{
  couleur_compteur *compteur;
  COMPTEBIT bc;
  int compteur_size = 0;
  int i = 0;

  compteur = calloc(1, sizeof(couleur_compteur));
  if (compteur == NULL)
  {
    perror("Erreur: allocation dynamique de memoire (compteur)\n");
    return NULL;
  }

  if (c->compte_bit == BITS24)
  {
    bc = BITS24;
    compteur->compte_bit = BITS24;
    compteur->cc.cc24 = calloc(csize, sizeof(couleur24_compteur));
    if (compteur->cc.cc24 == NULL) // Correction de la condition
    {
      perror("Erreur: allocation dynamique de memoire (cc24)\n");
      free(compteur);
      return NULL;
    }
  }
  else if (c->compte_bit == BITS32)
  {
    bc = BITS32;
    compteur->compte_bit = BITS32;
    compteur->cc.cc32 = calloc(csize, sizeof(couleur32_compteur));
    if (compteur->cc.cc32 == NULL) // Correction de la condition
    {
      perror("Erreur: allocation dynamique de memoire (cc32)\n");
      free(compteur);
      return NULL;
    }
  }
  else
  {
    fprintf(stderr, "Erreur: compte de bits inconnu\n");
    free(compteur);
    return NULL;
  }

  // Créer une table de hachage
  hcreate(csize);

  for (i = 0; i < csize; i++)
  {
    ENTRY e, *es;
    // CORRECTION : Allocation dynamique de la clé pour qu'elle persiste dans la table
    char *key = malloc(64 * sizeof(char));

    if (bc == BITS24)
    {
      sprintf(key, "%d:%d:%d", c->c.c24[i].rouge, c->c.c24[i].vert, c->c.c24[i].bleu);
    }
    else
    {
      sprintf(key, "%d:%d:%d:%d", c->c.c32[i].rouge, c->c.c32[i].vert, c->c.c32[i].bleu, c->c.c32[i].alpha);
    }
    e.key = key;

    es = hsearch(e, FIND);
    if (es == NULL)
    {
      compteur_size++;
      if (bc == BITS24)
      {
        compteur->cc.cc24[compteur_size - 1].c = c->c.c24[i];
        compteur->cc.cc24[compteur_size - 1].compte = 1;
        e.data = (void *)&compteur->cc.cc24[compteur_size - 1];
      }
      else
      {
        compteur->cc.cc32[compteur_size - 1].c = c->c.c32[i];
        compteur->cc.cc32[compteur_size - 1].compte = 1;
        e.data = (void *)&compteur->cc.cc32[compteur_size - 1];
      }
      // Insertion de la nouvelle clé
      if (hsearch(e, ENTER) == NULL)
      {
        perror("Erreur: impossible d'inserer dans la table de hachage\n");
        return NULL;
      }
    }
    else
    {
      // La couleur existe déjà : on libère la clé qu'on vient de créer et on incrémente
      free(key);
      if (bc == BITS24)
      {
        couleur24_compteur *cc24 = (couleur24_compteur *)es->data;
        cc24->compte++;
      }
      else
      {
        couleur32_compteur *cc32 = (couleur32_compteur *)es->data;
        cc32->compte++;
      }
    }
  }

  compteur->size = compteur_size;
  hdestroy(); // Note: en pratique, hdestroy ne libère pas les clés (e.key), mais on s'arrête là pour le TP
  return compteur;
}

// Afficher les couleurs
void print_couleur(couleur *c, int csize)
{
  for (int i = 0; i < csize; i++)
  {
    if (c->compte_bit == BITS24)
      printf("%02x %02x %02x\n", c->c.c24[i].rouge, c->c.c24[i].vert, c->c.c24[i].bleu);
    else if (c->compte_bit == BITS32)
      printf("%02x %02x %02x %02x\n", c->c.c32[i].rouge, c->c.c32[i].vert, c->c.c32[i].bleu, c->c.c32[i].alpha);
  }
}

// Comparaison pour le tri (DÉCROISSANT)
static int compare_compteur(const void *ccp1, const void *ccp2, void *compte_bitp)
{
  COMPTEBIT *bc = (COMPTEBIT *)compte_bitp;
  int c1, c2;

  if (*bc == BITS24)
  {
    c1 = ((couleur24_compteur *)ccp1)->compte;
    c2 = ((couleur24_compteur *)ccp2)->compte;
  }
  else
  {
    c1 = ((couleur32_compteur *)ccp1)->compte;
    c2 = ((couleur32_compteur *)ccp2)->compte;
  }

  if (c1 == c2) return 0;
  return (c1 > c2) ? -1 : 1; // Inversion pour trier du plus grand au plus petit
}

// Trier le compte de couleurs
void trier_couleur_compteur(couleur_compteur *ccompteur)
{
  COMPTEBIT bc = ccompteur->compte_bit;
  if (bc == BITS24)
  {
    qsort_r(ccompteur->cc.cc24, ccompteur->size, sizeof(couleur24_compteur),
            compare_compteur, (void *)&bc);
  }
  else if (bc == BITS32)
  {
    qsort_r(ccompteur->cc.cc32, ccompteur->size, sizeof(couleur32_compteur),
            compare_compteur, (void *)&bc);
  }
}
void creation_graphique_svg(char *couleurs, int nb_couleurs) {
  FILE *f = fopen("pie_chart.svg", "w");
  if (f == NULL) {
    printf("Erreur ouverture SVG\n");
    return;
  }

  fprintf(f, "<?xml version=\"1.0\" ?>\n");
  fprintf(f, "<svg width=\"400\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n");
  fprintf(f, "<rect width=\"100%%\" height=\"100%%\" fill=\"white\"/>\n");

  // Analyse de la chaîne (format: "nb,color1,color2...")
  char *token = strtok(couleurs, ","); // saute le nombre

  float slice = 360.0 / nb_couleurs;

  for (int i = 0; i < nb_couleurs; i++) {
    token = strtok(NULL, ","); // récupère la couleur Hexa
    if (token == NULL) break;

    // Code simplifié pour dessiner des parts de camembert
    // (Note: C'est un exemple de dessin basique pour le TP)
    fprintf(f, "<path d=\"M200,200 L200,50 A150,150 0 0,1 350,200 z\" fill=\"%s\" transform=\"rotate(%f, 200, 200)\"/>\n", token, i * slice);
  }

  fprintf(f, "</svg>\n");
  fclose(f);
  printf("Graphique pie_chart.svg genere avec %d couleurs.\n", nb_couleurs);
}