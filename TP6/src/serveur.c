#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


// Le prototype :
void creation_graphique_svg(char *couleurs, int nb_couleurs);

void erreur(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[2048];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) erreur("ERREUR ouverture socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5000;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        erreur("ERREUR sur le bind");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    printf("Serveur en attente sur le port %d...\n", portno);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) erreur("ERREUR sur accept");

        // 1. RÉCEPTION DU NOMBRE DE COULEURS (L'entier envoyé par le client)
        int nb_couleurs_attendues = 0;
        n = read(newsockfd, &nb_couleurs_attendues, sizeof(int));
        if (n < 0) erreur("ERREUR lecture du nombre de couleurs");

        printf("Le client demande l'analyse de %d couleurs.\n", nb_couleurs_attendues);

        // 2. RÉCEPTION DE LA CHAÎNE (ex: "10,#ffffff...")
        bzero(buffer, 2048);
        n = read(newsockfd, buffer, 2047);
        if (n < 0) erreur("ERREUR lecture socket");

        printf("Message recu: %s\n", buffer);

        // 3. GÉNÉRATION DU GRAPHIQUE
        // On passe le nombre dynamique reçu à la fonction de création du SVG
        creation_graphique_svg(buffer, nb_couleurs_attendues);

        // Tentative d'ouverture (ne marchera pas sur WSL mais crée le fichier)
        system("firefox pie_chart.svg &");

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}