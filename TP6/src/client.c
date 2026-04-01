#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "client.h"

/**
 * EXERCICE 5.5 : Fonction spécifique pour envoyer un calcul
 */
void envoi_operateur_numeros(int client_socket_fd, char operateur, int n1, int n2) {
    char message[1024];
    // On formate le message comme attendu par le serveur : "calcule : <op> <n1> <n2>"
    sprintf(message, "calcule : %c %d %d", operateur, n1, n2);

    printf("[CLIENT] Envoi du calcul au serveur...\n");
    write(client_socket_fd, message, strlen(message));
}

int main() {
    int client_socket_fd;
    struct sockaddr_in server_addr;
    char buffer_saisie[1024];
    char buffer_reponse[1024];

    // 1. Création de la socket
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_fd < 0) {
        perror("Erreur socket");
        return EXIT_FAILURE;
    }

    // 2. Configuration de l'adresse du serveur
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 3. Connexion au serveur
    if (connect(client_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erreur connexion");
        return EXIT_FAILURE;
    }

    printf("Connecté au serveur ! (Tapez vos messages ou 'calcule : + 10 20')\n");

    while (1) {
        printf("> ");
        fflush(stdout);

        // Lecture de la saisie utilisateur
        if (fgets(buffer_saisie, sizeof(buffer_saisie), stdin) == NULL) break;
        buffer_saisie[strcspn(buffer_saisie, "\n")] = 0; // Nettoyage du \n

        // --- LOGIQUE EXERCICE 5.5 ---
        // Si l'utilisateur tape "calcule : + 10 20"
        if (strncmp(buffer_saisie, "calcule :", 9) == 0) {
            char op;
            int v1, v2;
            // On extrait les valeurs pour appeler la fonction demandée
            if (sscanf(buffer_saisie + 10, " %c %d %d", &op, &v1, &v2) == 3) {
                envoi_operateur_numeros(client_socket_fd, op, v1, v2);
            } else {
                printf("Format incorrect. Utilisez : calcule : <op> <n1> <n2>\n");
                continue;
            }
        }
        // Sinon, envoi normal (Exercice 5.4)
        else {
            write(client_socket_fd, buffer_saisie, strlen(buffer_saisie));
        }

        // 4. Attente de la réponse du serveur
        memset(buffer_reponse, 0, sizeof(buffer_reponse));
        int n = read(client_socket_fd, buffer_reponse, sizeof(buffer_reponse) - 1);
        if (n > 0) {
            printf("Réponse du serveur : %s\n", buffer_reponse);
        } else {
            printf("Serveur déconnecté.\n");
            break;
        }
    }

    close(client_socket_fd);
    return 0;
}