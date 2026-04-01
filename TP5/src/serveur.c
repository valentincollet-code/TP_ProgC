#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "serveur.h"

int socketfd;

/**
 * Envoie un message au client.
 */
int renvoie_message(int client_socket_fd, char *data) {
    int data_size = write(client_socket_fd, (void *)data, strlen(data));
    if (data_size < 0) {
        perror("Erreur d'écriture");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * Gère le calcul demandé par le client (Exercice 5.5).
 * Format attendu : "calcule : <op> <n1> <n2>"
 */
void recois_numeros_calcule(int client_fd, char *data) {
    char op;
    int n1, n2, res = 0;

    // On extrait l'opérateur et les deux nombres du message
    // data + 10 permet de sauter la chaîne "calcule : "
    if (sscanf(data + 10, " %c %d %d", &op, &n1, &n2) == 3) {
        int erreur = 0;

        if (op == '+') res = n1 + n2;
        else if (op == '-') res = n1 - n2;
        else if (op == '*') res = n1 * n2;
        else if (op == '/') {
            if (n2 != 0) res = n1 / n2;
            else erreur = 1;
        } else {
            erreur = 1;
        }

        char reponse[1024];
        if (!erreur) {
            sprintf(reponse, "calcul : %d", res);
            printf("[SERVEUR] Calcul effectué : %d %c %d = %d\n", n1, op, n2, res);
        } else {
            sprintf(reponse, "calcul : Erreur (opérateur invalide ou div par 0)");
        }

        // Envoi du résultat au client
        write(client_fd, reponse, strlen(reponse));
    }
}

/**
 * Fonction interactive pour répondre manuellement (Exercice 5.4).
 */
int recois_envoie_message(int client_socket_fd, char *data) {
    printf("\n[CLIENT] : %s\n", data);

    char reponse_serveur[1024];
    printf("Tape ta réponse manuelle : ");
    fflush(stdout);

    if (fgets(reponse_serveur, sizeof(reponse_serveur), stdin) != NULL) {
        reponse_serveur[strcspn(reponse_serveur, "\n")] = 0;
        return renvoie_message(client_socket_fd, reponse_serveur);
    }
    return EXIT_SUCCESS;
}

/**
 * Boucle de gestion des messages d'un client.
 */
void gerer_client(int client_socket_fd) {
    char data[1024];
    while (1) {
        memset(data, 0, sizeof(data));
        int data_size = read(client_socket_fd, data, sizeof(data));

        if (data_size <= 0) break;

        // On vérifie si le message commence par "calcule :"
        if (strncmp(data, "calcule :", 9) == 0) {
            recois_numeros_calcule(client_socket_fd, data);
        } else {
            // Sinon, on reste sur le mode interactif de l'exercice 5.4
            recois_envoie_message(client_socket_fd, data);
        }
    }
    close(client_socket_fd);
}

void gestionnaire_ctrl_c(int signal) {
    printf("\nArrêt du serveur...\n");
    if (socketfd != -1) close(socketfd);
    exit(0);
}

int main() {
    struct sockaddr_in server_addr;
    int option = 1;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return EXIT_FAILURE;
    }

    signal(SIGINT, gestionnaire_ctrl_c);
    listen(socketfd, 10);

    // --- ON FORCE L'AFFICHAGE ICI ---
    printf("SERVEUR 5.5 OK - Prêt pour calculs et messages...\n");
    fflush(stdout);

    while (1) {
        struct sockaddr_in client_addr;
        unsigned int len = sizeof(client_addr);
        int client_fd = accept(socketfd, (struct sockaddr *)&client_addr, &len);

        if (client_fd >= 0) {
            printf("\n--- Nouveau Client --- \n");
            fflush(stdout);
            gerer_client(client_fd);
        }
    }
    return 0;
}