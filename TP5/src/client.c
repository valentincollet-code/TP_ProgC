#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"

/* * SECURITÉ : Si PORT est déjà défini dans client.h (8089),
 * cette ligne ne fera rien. Sinon, elle met 8080.
 */
#ifndef PORT
#define PORT 8080
#endif

int lire_note(int num_etudiant, int num_note) {
    char chemin[100];
    int note = 0;
    sprintf(chemin, "../etudiant/%d/note%d.txt", num_etudiant, num_note);
    FILE *f = fopen(chemin, "r");
    if (f != NULL) {
        fscanf(f, "%d", &note);
        fclose(f);
    }
    return note;
}

int demander_calcul(int sockfd, char op, int n1, int n2) {
    char buffer[1024];
    memset(buffer, 0, 1024);
    sprintf(buffer, "%c %d %d", op, n1, n2);
    write(sockfd, buffer, strlen(buffer));

    memset(buffer, 0, 1024);
    read(sockfd, buffer, 1023);

    int resultat = 0;
    sscanf(buffer, "%d", &resultat);
    return resultat;
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;

    /* Utilise le PORT (sera 8089 si client.h est inclus) */
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        perror("Échec de la connexion");
        exit(1);
    }

    printf("Connecté au serveur sur le port %d\n", PORT);

    int somme_classe = 0;
    for (int e = 1; e <= 5; e++) {
        int n1 = lire_note(e, 1);
        int n2 = lire_note(e, 2);
        int n3 = lire_note(e, 3);
        int n4 = lire_note(e, 4);
        int n5 = lire_note(e, 5);

        int s1 = demander_calcul(sockfd, '+', n1, n2);
        int s2 = demander_calcul(sockfd, '+', n3, n4);
        int s3 = demander_calcul(sockfd, '+', s1, s2);
        int total_etudiant = demander_calcul(sockfd, '+', s3, n5);

        printf("Somme Étudiant %d : %d\n", e, total_etudiant);
        somme_classe = demander_calcul(sockfd, '+', somme_classe, total_etudiant);
    }

    int moyenne_classe = demander_calcul(sockfd, '/', somme_classe, 25);
    printf("\nMOYENNE GENERALE : %d\n", moyenne_classe);

    close(sockfd);
    return 0;
}