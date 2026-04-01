#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// Fonction pour lire une note spécifique dans les dossiers
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

// Fonction utilitaire pour envoyer le calcul et recevoir le résultat (entier)
int demander_calcul(int sockfd, char op, int n1, int n2) {
    char buffer[1024];
    // On formate exactement comme demandé : "+ note1 note2"
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
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        perror("Échec de la connexion");
        exit(1);
    }

    int somme_classe = 0;

    // Boucle sur les 5 étudiants
    for (int e = 1; e <= 5; e++) {
        int n1 = lire_note(e, 1);
        int n2 = lire_note(e, 2);
        int n3 = lire_note(e, 3);
        int n4 = lire_note(e, 4);
        int n5 = lire_note(e, 5);

        // Application stricte de l'exemple de l'énoncé :
        int somme12 = demander_calcul(sockfd, '+', n1, n2); // "+ note1 note2"
        int somme34 = demander_calcul(sockfd, '+', n3, n4); // "+ note3 note4"
        int somme1234 = demander_calcul(sockfd, '+', somme12, somme34);
        int somme_totale_etudiant = demander_calcul(sockfd, '+', somme1234, n5); // "+ somme note5"

        printf("Somme des notes de l'étudiant %d : %d\n", e, somme_totale_etudiant);

        // On ajoute la somme de cet étudiant à la somme globale de la classe
        somme_classe = demander_calcul(sockfd, '+', somme_classe, somme_totale_etudiant);
    }

    // Calcul de la moyenne de la classe (division par 25 car 5 étudiants * 5 notes)
    // "/ somme 25"
    int moyenne_classe = demander_calcul(sockfd, '/', somme_classe, 25);

    printf("\n======================================\n");
    printf("MOYENNE GENERALE DE LA CLASSE : %d\n", moyenne_classe);
    printf("======================================\n");

    close(sockfd);
    return 0;
}