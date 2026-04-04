#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "serveur.h"

// Fonction imposée par l'Exo 5.5
void recois_numeros_calcule(int client_fd, char *message) {
    char op;
    int n1, n2, res = 0;

    if (sscanf(message, "calcule : %c %d %d", &op, &n1, &n2) == 3) {
        if (op == '+') res = n1 + n2;
        else if (op == '-') res = n1 - n2;
        else if (op == '*') res = n1 * n2;
        else if (op == '/' && n2 != 0) res = n1 / n2;

        char reponse[256];
        sprintf(reponse, "calcule : %d", res);
        write(client_fd, reponse, strlen(reponse));

        // Log optionnel pour voir le serveur travailler
        printf("[SERVEUR] %d %c %d = %d\n", n1, op, n2, res);
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int opt = 1, addrlen = sizeof(address);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind échoué");
        exit(EXIT_FAILURE);
    }
    listen(server_fd, 5);

    printf("SERVEUR OK (Port %d)...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) continue;

        while (1) {
            memset(buffer, 0, 1024);
            int n = read(client_fd, buffer, 1024);
            if (n <= 0) break; // Client déconnecté

            if (strncmp(buffer, "calcule :", 9) == 0) {
                recois_numeros_calcule(client_fd, buffer);
            }
        }
        close(client_fd);
    }
    return 0;
}