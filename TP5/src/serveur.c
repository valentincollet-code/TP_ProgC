#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "serveur.h" // Contient le #define PORT 8089

// Fonction de calcul pour l'exercice 5.4
void envoie_operateur_numeros(int client_fd, char *message) {
    char op;
    int n1, n2;

    // Découpage du message reçu (ex: "+ 10 20")
    if (sscanf(message, " %c %d %d", &op, &n1, &n2) == 3) {
        int res = 0;
        switch (op) {
            case '+': res = n1 + n2; break;
            case '-': res = n1 - n2; break;
            case '*': res = n1 * n2; break;
            case '/': res = (n2 != 0) ? n1 / n2 : 0; break;
            default:  res = 0; break;
        }

        char reponse[256];
        sprintf(reponse, "%d", res);
        // On renvoie le résultat au client
        write(client_fd, reponse, strlen(reponse));
        printf("[LOG] Calcul : %d %c %d = %d\n", n1, op, n2, res);
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // 1. Création de la socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket échouée");
        exit(EXIT_FAILURE);
    }

    // 2. Option pour redémarrer le serveur rapidement sans erreur "Address already in use"
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3. Configuration de l'adresse (Utilise le PORT du header)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT); // <--- Ici, PORT sera 8089 (ou 8080 selon ton .h)

    // 4. Liaison (Bind)
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind échoué");
        exit(EXIT_FAILURE);
    }

    // 5. Écoute
    if (listen(server_fd, 3) < 0) {
        perror("Listen échoué");
        exit(EXIT_FAILURE);
    }

    printf("SERVEUR OK - Écoute sur le port %d...\n", PORT);

    while (1) {
        // Attente d'un client
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) {
            perror("Accept échoué");
            continue;
        }

        printf("Client connecté !\n");

        // Dialogue avec le client
        while (1) {
            memset(buffer, 0, 1024);
            int valread = read(client_fd, buffer, 1024);

            if (valread <= 0) {
                printf("Client déconnecté.\n");
                break;
            }

            // Traitement du message (Exercice 5.4)
            envoie_operateur_numeros(client_fd, buffer);
        }
        close(client_fd);
    }

    close(server_fd);
    return 0;
}