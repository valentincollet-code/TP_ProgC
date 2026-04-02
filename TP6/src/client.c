#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

#include "client.h"
#include "bmp.h"
#include "cJSON.h" // N'oublie pas d'inclure cJSON

void erreur(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s fichier.bmp\n", argv[0]);
        exit(0);
    }

    // 1. Demander le nombre de couleurs
    int nb_couleurs;
    printf("Combien de couleurs voulez-vous analyser (max 30) ? ");
    if (scanf("%d", &nb_couleurs) != 1 || nb_couleurs <= 0 || nb_couleurs > 30) {
        printf("Nombre invalide, utilisation par défaut : 10\n");
        nb_couleurs = 10;
    }

    // 2. Analyse de l'image
    couleur_compteur *cc = analyse_bmp_image(argv[1]);
    if (cc == NULL) {
        fprintf(stderr, "Erreur lors de l'analyse de l'image.\n");
        exit(1);
    }

    // 3. Connexion au serveur
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

    // --- MODIFICATION EXERCICE 6.3 : CONSTRUCTION DU JSON ---

    // Création de l'objet racine { }
    cJSON *root = cJSON_CreateObject();

    // Ajout de "code": "couleurs"
    cJSON_AddStringToObject(root, "code", "couleurs");

    // Création du tableau "valeurs": [ ]
    cJSON *valeurs = cJSON_CreateArray();
    for (int i = 0; i < nb_couleurs; i++) {
        char hex_color[8];
        sprintf(hex_color, "#%02x%02x%02x",
                cc->cc.cc24[i].c.rouge,
                cc->cc.cc24[i].c.vert,
                cc->cc.cc24[i].c.bleu);

        // On ajoute la chaîne hexadécimale au tableau
        cJSON_AddItemToArray(valeurs, cJSON_CreateString(hex_color));
    }
    cJSON_AddItemToObject(root, "valeurs", valeurs);

    // Conversion de l'objet JSON en chaîne de caractères (string)
    char *json_string = cJSON_PrintUnformatted(root);

    // 4. ENVOI DU MESSAGE JSON
    // On envoie maintenant une seule chaîne de caractères contenant tout le JSON
    n = write(sockfd, json_string, strlen(json_string));
    if (n < 0) erreur("ERREUR envoi JSON");

    printf("Données JSON envoyées avec succès :\n%s\n", json_string);

    // 5. NETTOYAGE
    free(json_string);  // Libère la chaîne générée par cJSON_Print
    cJSON_Delete(root); // Libère la structure de l'objet JSON
    close(sockfd);

    return 0;
}