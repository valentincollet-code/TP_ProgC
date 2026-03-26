cmake_minimum_required(VERSION 3.10)
project(TP_Programmation_C)

# On indique au compilateur d'aller chercher les headers (.h) dans TP4/src
include_directories(TP4/src)

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
