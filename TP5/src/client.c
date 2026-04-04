#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"

#ifndef PORT
#define PORT 8089
#endif

// Lit la note dans le dossier etudiant (TP4)
int lire_note(int num_etudiant, int num_note) {
    char chemin[128];
    int note = 0;
    sprintf(chemin, "../etudiant/%d/note%d.txt", num_etudiant, num_note);
    FILE *f = fopen(chemin, "r");
    if (f != NULL) {
        if (fscanf(f, "%d", &note) != 1) note = 0;
        fclose(f);
    }
    return note;
}

// Fonction demandée par l'énoncé
int envoie_operateur_numeros(int sockfd, char op, int n1, int n2) {
    char buffer[1024];
    memset(buffer, 0, 1024);

    // Envoie le message au serveur (format compatible 5.6)
    sprintf(buffer, "%c %d %d", op, n1, n2);
    write(sockfd, buffer, strlen(buffer));

    memset(buffer, 0, 1024);
    read(sockfd, buffer, 1023);

    int resultat = 0;
    sscanf(buffer, "calcule : %d", &resultat);
    return resultat;
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        perror("Connection failure");
        exit(1);
    }

    printf("Connecté au serveur (Port %d)\n", PORT);

    int somme_classe = 0;

    // Boucle sur les 5 étudiants pour calculer les sommes
    for (int e = 1; e <= 5; e++) {
        int n1 = lire_note(e, 1);
        int n2 = lire_note(e, 2);
        int n3 = lire_note(e, 3);
        int n4 = lire_note(e, 4);
        int n5 = lire_note(e, 5);

        // Sommes successives envoyées au serveur
        int s12 = envoie_operateur_numeros(sockfd, '+', n1, n2);
        int s34 = envoie_operateur_numeros(sockfd, '+', n3, n4);
        int s1234 = envoie_operateur_numeros(sockfd, '+', s12, s34);
        int total_etudiant = envoie_operateur_numeros(sockfd, '+', s1234, n5);

        printf("Somme Étudiant %d : %d\n", e, total_etudiant);

        // Cumul pour la moyenne de la classe
        somme_classe = envoie_operateur_numeros(sockfd, '+', somme_classe, total_etudiant);
    }

    // Calcul de la moyenne générale (25 notes au total) via le serveur
    int moyenne = envoie_operateur_numeros(sockfd, '/', somme_classe, 25);

    printf("\n========================================\n");
    printf(">>> MOYENNE GENERALE DE LA CLASSE : %d\n", moyenne);
    printf("========================================\n");

    close(sockfd);
    return 0;
}