#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "bmp.h"

void erreur(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[2048]; // Buffer assez grand pour les couleurs

    if (argc < 2) {
        fprintf(stderr, "Usage: %s fichier.bmp\n", argv[0]);
        exit(0);
    }

    // 1. Demander le nombre de couleurs à l'utilisateur
    int nb_couleurs;
    printf("Combien de couleurs voulez-vous analyser (max 30) ? ");
    if (scanf("%d", &nb_couleurs) != 1 || nb_couleurs <= 0 || nb_couleurs > 30) {
        printf("Nombre invalide, utilisation par défaut : 10\n");
        nb_couleurs = 10;
    }

    // 2. Analyse de l'image (via bmp.c)
    couleur_compteur *cc = analyse_bmp_image(argv[1]);
    if (cc == NULL) {
        fprintf(stderr, "Erreur lors de l'analyse de l'image.\n");
        exit(1);
    }

    // 3. Connexion au serveur (Port 5000 par défaut ici)
    portno = 5000;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) erreur("ERREUR ouverture socket");

    server = gethostbyname("localhost");
    if (server == NULL) erreur("ERREUR, hôte inexistant");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        erreur("ERREUR connexion");

    // 4. ENVOI DU NOMBRE DE COULEURS
    // On envoie l'entier brut au serveur
    n = write(sockfd, &nb_couleurs, sizeof(int));
    if (n < 0) erreur("ERREUR envoi nombre couleurs");

    // 5. Préparation de la chaîne de couleurs (ex: "10,#ffffff,#000000...")
    // On commence par mettre le nombre dans la chaîne
    sprintf(buffer, "%d", nb_couleurs);

    // On ajoute chaque couleur trouvée
    for (int i = 0; i < nb_couleurs; i++) {
        char temp[9];
        // On transforme les composantes R,G,B en Hexadécimal
        // Correction pour accéder aux membres R, G, B correctement
        sprintf(temp, ",#%02x%02x%02x",
                cc->cc.cc24[i].c.rouge,
                cc->cc.cc24[i].c.vert,
                cc->cc.cc24[i].c.bleu);
        strcat(buffer, temp);
    }

    // 6. ENVOI DE LA CHAÎNE DE COULEURS
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) erreur("ERREUR envoi chaine couleurs");

    printf("Données envoyées avec succès (%d couleurs).\n", nb_couleurs);

    close(sockfd);
    return 0;
}