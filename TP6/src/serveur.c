#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "cJSON.h" // Indispensable !

// Le prototype (on garde ta fonction existante)
void creation_graphique_svg(char *couleurs, int nb_couleurs);

void erreur(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[4096]; // Augmenté un peu pour être large avec le JSON
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) erreur("ERREUR ouverture socket");

    // Option pour réutiliser le port immédiatement après un arrêt/relance
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5000;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        erreur("ERREUR sur le bind");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    printf("Serveur JSON en attente sur le port %d...\n", portno);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0) erreur("ERREUR sur accept");

        // --- MODIFICATION EXERCICE 6.3 : RÉCEPTION ET ANALYSE JSON ---

        bzero(buffer, 4096);
        n = read(newsockfd, buffer, 4095);
        if (n < 0) erreur("ERREUR lecture socket");

        // 1. Parser la chaîne reçue pour en faire un objet JSON
        cJSON *json = cJSON_Parse(buffer);
        if (json == NULL) {
            printf("Erreur : Message reçu n'est pas un JSON valide.\n");
            close(newsockfd);
            continue;
        }

        // 2. Extraire le code d'opération
        cJSON *code = cJSON_GetObjectItemCaseSensitive(json, "code");
        if (cJSON_IsString(code) && (strcmp(code->valuestring, "couleurs") == 0)) {

            // 3. Extraire le tableau de valeurs
            cJSON *valeurs = cJSON_GetObjectItemCaseSensitive(json, "valeurs");
            int nb_couleurs = cJSON_GetArraySize(valeurs);
            printf("Reçu : %d couleurs via JSON.\n", nb_couleurs);

            // 4. Reconstruire la chaîne pour ton ancienne fonction SVG
            // (Format attendu par ta fonction : "nb,#hex,#hex...")
            char chaine_svg[4096];
            sprintf(chaine_svg, "%d", nb_couleurs);

            for (int i = 0; i < nb_couleurs; i++) {
                cJSON *item = cJSON_GetArrayItem(valeurs, i);
                strcat(chaine_svg, ",");
                strcat(chaine_svg, item->valuestring);
            }

            // 5. Génération du graphique
            creation_graphique_svg(chaine_svg, nb_couleurs);
            printf("Graphique SVG mis à jour.\n");

            // 6. Répondre au client (en JSON comme demandé par l'exercice)
            cJSON *reponse = cJSON_CreateObject();
            cJSON_AddStringToObject(reponse, "statut", "OK");
            cJSON_AddNumberToObject(reponse, "message", nb_couleurs);
            char *reponse_str = cJSON_PrintUnformatted(reponse);

            write(newsockfd, reponse_str, strlen(reponse_str));

            free(reponse_str);
            cJSON_Delete(reponse);

            // Tentative d'ouverture
            system("firefox pie_chart.svg &");
        }

        // Nettoyage de l'objet JSON de réception
        cJSON_Delete(json);
        close(newsockfd);
    }

    close(sockfd);
    return 0;
}