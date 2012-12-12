#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>

#define TAILLE 100 
#define PORT 9600

int main(int argc, char* argv[]){

	int socket_serveur, acc;
	struct sockaddr_in adresse_serveur;
	struct sockaddr_in adresse_client;
	int taille_adresse;
	char buffer[TAILLE];

	if((socket_serveur = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		fprintf(stderr, "Erreur à la création de la socket\n");
		exit(-1);
	}
	bzero((char *)&adresse_serveur, sizeof(adresse_serveur));
	adresse_serveur.sin_family = AF_INET;
	adresse_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
	adresse_serveur.sin_port = htons(PORT);
	bind(socket_serveur, (struct sockaddr*)&adresse_serveur, sizeof(adresse_serveur));
	listen(socket_serveur, 5);
	taille_adresse = sizeof(adresse_client);
	while(1){	
		acc = accept(socket_serveur, (struct sockaddr*) &adresse_client, &taille_adresse);
		read(acc, buffer, 100);
		sleep(1);
		write(acc, "ok!", 100);
	}
	shutdown(socket_serveur, SHUT_RDWR);
	close(socket_serveur);

	return EXIT_SUCCESS;
}
