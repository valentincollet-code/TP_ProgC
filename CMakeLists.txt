cmake_minimum_required(VERSION 3.10)
project(TP_Programmation_C)

# On indique au compilateur d'aller chercher les headers (.h)
# dans les dossiers du TP4 et du TP6
include_directories(TP4/src TP6/src)

# --- EXERCICE 4.1 : LA CALCULATRICE ---
add_executable(calculatrice
        TP4/src/main.c
        TP4/src/operator.c
)

# --- EXERCICE 4.2 : GESTION DE FICHIERS ---
add_executable(gestion_fichiers
        TP4/src/main_file.c
        TP4/src/fichier.c
)

# --- EXERCICE 6.3 : COMMUNICATION JSON (NOUVEAU) ---
# On crée deux exécutables distincts qui partagent la bibliothèque cJSON

# Le Client
add_executable(client_json
        TP6/src/client.c
        TP6/src/cJSON.c
)

# Le Serveur
add_executable(serveur_json
        TP6/src/serveur.c
        TP6/src/cJSON.c
)