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

int renvoie_message(int client_socket_fd, char *data) {
    int data_size = write(client_socket_fd, (void *)data, strlen(data));
    return (data_size < 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

int recois_envoie_message(int client_socket_fd, char *data) {
    // 1. On affiche ce que le client a envoyé
    printf("\n[CLIENT] : %s\n", data);

    // 2. On prépare la saisie de TA réponse
    char reponse_serveur[1024];
    printf("Tape ta réponse ici : ");
    fflush(stdout); // Indispensable pour voir le texte

    // 3. Le programme s'arrête ici pour attendre ton clavier
    if (fgets(reponse_serveur, sizeof(reponse_serveur), stdin) != NULL) {
        reponse_serveur[strcspn(reponse_serveur, "\n")] = 0; // Nettoie le 'Entrée'
        return renvoie_message(client_socket_fd, reponse_serveur);
    }
    return EXIT_SUCCESS;
}

void gerer_client(int client_socket_fd) {
    char data[1024];
    while (1) {
        memset(data, 0, sizeof(data));
        int data_size = read(client_socket_fd, data, sizeof(data));
        if (data_size <= 0) break;
        recois_envoie_message(client_socket_fd, data);
    }
    close(client_socket_fd);
}

void gestionnaire_ctrl_c(int signal) {
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

    bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    signal(SIGINT, gestionnaire_ctrl_c);
    listen(socketfd, 10);

    printf("SERVEUR OK - En attente du client...\n");

    while (1) {
        struct sockaddr_in client_addr;
        unsigned int len = sizeof(client_addr);
        int client_fd = accept(socketfd, (struct sockaddr *)&client_addr, &len);
        if (client_fd >= 0) {
            printf("\nClient connecté !");
            gerer_client(client_fd); // Pas de fork ici !
            printf("\nClient déconnecté, retour en attente...\n");
        }
    }
    return 0;
}