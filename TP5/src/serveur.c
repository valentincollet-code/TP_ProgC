#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// Fonction demandée par l'énoncé pour effectuer le calcul
void envoie_operateur_numeros(int client_fd, char *message) {
    char op;
    int n1, n2;

    // Le serveur lit le format envoyé par le client : ex "+ 15 10"
    if (sscanf(message, " %c %d %d", &op, &n1, &n2) == 3) {
        int res = 0;
        if (op == '+') res = n1 + n2;
        else if (op == '-') res = n1 - n2;
        else if (op == '*') res = n1 * n2;
        else if (op == '/' && n2 != 0) res = n1 / n2;

        char reponse[256];
        sprintf(reponse, "%d", res); // On renvoie juste le résultat brut
        write(client_fd, reponse, strlen(reponse));
        printf("[SERVEUR] Calcul effectué : %d %c %d = %d\n", n1, op, n2, res);
    } else {
        write(client_fd, "0", 1); // En cas d'erreur de format
    }
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    printf("SERVEUR OK - Prêt à calculer...\n");

    // Boucle infinie pour accepter les clients un par un
    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client_fd < 0) continue;

        // Boucle infinie pour lire les messages du client connecté
        while (1) {
            memset(buffer, 0, 1024);
            int valread = read(client_fd, buffer, 1024);

            if (valread <= 0) {
                break; // Le client s'est déconnecté
            }

            envoie_operateur_numeros(client_fd, buffer);
        }
        close(client_fd);
    }
    return 0;
}