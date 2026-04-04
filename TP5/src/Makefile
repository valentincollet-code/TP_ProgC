# Définition du compilateur et des options
CC = gcc
CFLAGS = -Wall -Wextra -g

# Noms des exécutables finals
SERVER = serveur
CLIENT = client

# Liste des fichiers objets
SOBJS = serveur.o
COBJS = client.o

# Règle par défaut : compile tout
all: $(SERVER) $(CLIENT)

# Règle pour l'exécutable serveur
$(SERVER): $(SOBJS)
	$(CC) $(CFLAGS) -o $(SERVER) $(SOBJS)

# Règle pour l'exécutable client
$(CLIENT): $(COBJS)
	$(CC) $(CFLAGS) -o $(CLIENT) $(COBJS)

# Règle générique pour créer les .o à partir des .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de nettoyage pour recommencer à zéro
clean:
	rm -f *.o $(SERVER) $(CLIENT)

# Empêche la confusion si des fichiers s'appellent 'clean' ou 'all'
.PHONY: all clean