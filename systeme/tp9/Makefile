all: serveur client

client: client.o socket.o
	@echo "Compilation de $@"
	gcc client.o socket.o -o client

client.o: client.c socket.h
	@echo "Compilation de client.c"
	gcc -c client.c

socket.o: socket.c socket.h
	@echo "Compilation de socket.c"
	gcc -c socket.c

serveur: serveur.o socket.o
	@echo "Compilation de $@"
	gcc serveur.o socket.o -o serveur

serveur.o: serveur.c socket.h
	@echo "Compilation de serveur.c"
	gcc -c serveur.c

clean:
	-rm *.o

cleanCS:
	-rm client
	-rm serveur
