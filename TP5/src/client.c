#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.h"

// Lit une note dans le dossier etudiant (TP4)
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

// Fonction imposée par l'Exo 5.5
int envoie_operateur_numeros(int sockfd, char op, int n1, int n2) {
    char buffer[1024];
    memset(buffer, 0, 1024);

    // Format d'envoi imposé
    sprintf(buffer, "calcule : %c %d %d", op, n1, n2);
    write(sockfd, buffer, strlen(buffer));

    memset(buffer, 0, 1024);
    read(sockfd, buffer, 1023);

    int resultat = 0;
    // On extrait le nombre après "calcule : "
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
        perror("Connexion échouée");
        exit(1);
    }

    // --- AFFICHAGE EXACT DE TON IMAGE ---
    printf("Connecté au serveur (Port %d)\n", PORT);

    // Test Exo 5.5
    int res_test = envoie_operateur_numeros(sockfd, '+', 23, 45);
    printf("Test Exo 5.5 (23 + 45) -> calcule : %d\n\n", res_test);

    int somme_classe = 0;
    for (int e = 1; e <= 5; e++) {
        int n[5];
        for(int i=0; i<5; i++) n[i] = lire_note(e, i+1);

        // Calculs intermédiaires via le serveur
        int s1 = envoie_operateur_numeros(sockfd, '+', n[0], n[1]);
        int s2 = envoie_operateur_numeros(sockfd, '+', n[2], n[3]);
        int s3 = envoie_operateur_numeros(sockfd, '+', s1, s2);
        int total_etudiant = envoie_operateur_numeros(sockfd, '+', s3, n[4]);

        printf("Étudiant %d | Somme : %d\n", e, total_etudiant);
        somme_classe = envoie_operateur_numeros(sockfd, '+', somme_classe, total_etudiant);
    }

    int moyenne = envoie_operateur_numeros(sockfd, '/', somme_classe, 25);

    printf("\n========================================\n");
    printf("MOYENNE GENERALE DE LA CLASSE : %d\n", moyenne);
    printf("========================================\n");

    close(sockfd);
    return 0;
}