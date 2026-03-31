/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

couleur_compteur *analyse_bmp_image(char *nom_de_fichier)
{
  couleur_compteur *cc = NULL;

  // 1. Ouverture du fichier
  int fd = open(nom_de_fichier, O_RDONLY);
  if (fd < 0)
  {
    perror("Erreur: open");
    return NULL;
  }

  bmp_header bheader;
  bmp_info_header binfo_header;

  // 2. Lecture du premier en-tête (Général)
  ssize_t compte = read(fd, &bheader, sizeof(bheader));
  if (compte <= 0)
  {
    perror("Erreur: read header");
    close(fd);
    return NULL;
  }

  // 3. Vérification du format BMP (Signature 'BM')
  if (bheader.type != 0x4D42)
  {
    fprintf(stderr, "Erreur: Ce n'est pas un fichier BMP valide.\n");
    close(fd);
    return NULL;
  }

  // 4. Lecture du second en-tête (Infos techniques)
  compte = read(fd, &binfo_header, sizeof(binfo_header));
  if (compte <= 0)
  {
    perror("Erreur: read info header");
    close(fd);
    return NULL;
  }

  // --- BLOC DE DEBUG (Placé au bon moment !) ---
  printf("\n--- DEBUG BMP ---\n");
  printf("Fichier: %s\n", nom_de_fichier);
  printf("Offset pixels: %u\n", bheader.offset);
  printf("Largeur: %u\n", binfo_header.largeur);
  printf("Hauteur: %d\n", (int)binfo_header.hauteur);
  printf("Bits par pixel: %u\n", binfo_header.compte_bit);
  printf("----------------\n");

  // 5. Se positionner au début des données pixels
  if (lseek(fd, bheader.offset, SEEK_SET) < 0)
  {
    perror("Erreur: lseek");
    close(fd);
    return NULL;
  }

  // 6. Lecture des pixels selon le format (24 ou 32 bits)
  if (binfo_header.compte_bit == 32)
  {
    int nb_pixels = binfo_header.largeur * binfo_header.hauteur;
    couleur32 *c32 = calloc(nb_pixels, sizeof(couleur32));
    read(fd, c32, nb_pixels * sizeof(couleur32));

    couleur c;
    c.compte_bit = BITS32;
    c.c.c32 = c32;
    cc = compte_couleur(&c, nb_pixels);
    trier_couleur_compteur(cc);
  }
  else if (binfo_header.compte_bit == 24)
  {
    int nb_pixels = binfo_header.largeur * binfo_header.hauteur;
    if (nb_pixels < 0) nb_pixels = -nb_pixels; // Gestion hauteur négative

    couleur24 *c24 = calloc(nb_pixels, sizeof(couleur24));

    // On lit les pixels.
    // Attention: cette méthode ignore le padding, ce qui est OK pour 800px de large
    ssize_t lus = read(fd, c24, nb_pixels * sizeof(couleur24));

    printf("DEBUG: Pixels attendus: %d, Octets lus: %zd\n", nb_pixels, lus);

    // Regardons la couleur du tout premier pixel lu
    printf("DEBUG: Premier pixel: R=%02x G=%02x B=%02x\n", c24[0].rouge, c24[0].vert, c24[0].bleu);

    couleur c;
    c.compte_bit = BITS24;
    c.c.c24 = c24;
    cc = compte_couleur(&c, nb_pixels);
    trier_couleur_compteur(cc);
  }

  close(fd);
  return cc;
}