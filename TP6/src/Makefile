CLIENT_OBJS = client.o bmp.o couleur.o cJSON.o
SERVER_OBJS = serveur.o couleur.o bmp.o cJSON.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS)
	gcc -Wall -Werror -ggdb3 -o $(SERVER) $(SERVER_OBJS) -lm

$(CLIENT): $(CLIENT_OBJS)
	gcc -Wall -Werror -ggdb3 -o $(CLIENT) $(CLIENT_OBJS) -lm

.c.o:
	gcc -Wall -Werror -ggdb3 -c $< -o $@

clean:
	rm -f *.o $(SERVER) $(CLIENT) pie_chart.svg