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
#define h_addr h_addr_list[0]

int main(int argc, char * argv[]){

	int socket_client;
	struct sockaddr_in adresse_serveur;
	struct hostent* info_serveur;
	char buffer[TAILLE];
	char* nomMachine;

	nomMachine = argv[1];
	//printf("Votre message: %s\n", buffer);
	//printf("Nom de machine: %s\n", nomMachine);
	if((socket_client = socket(AF_INET, SOCK_DGRAM, 0) == -1)){
		fprintf(stderr, "Erreur à la création de la socket\n");
		exit(-1);
	}
	info_serveur = gethostbyname(argv[1]);
	bzero((char *)&adresse_serveur, sizeof(adresse_serveur));
	adresse_serveur.sin_family = AF_INET;
	//adresse_serveur.sin_addr.s_addr = (struct in_addr*)info_serveur->h_addr;
	bcopy((char *)info_serveur->h_addr,(char *)&adresse_serveur.sin_addr.s_addr, info_serveur->h_length);
	adresse_serveur.sin_port = htons(PORT);
	if(connect(socket_client, (struct sockaddr*) &adresse_serveur, sizeof(adresse_serveur)) == -1){
		fprintf(stderr, "erreur connect");
		exit(-2);
	}
	printf("Entrez le message à transmettre: ");
	fgets(buffer, TAILLE, stdin);
	write(socket_client, buffer, 100);
	sleep(1);
	//read(socket_client, buffer, strlen(buffer));
	shutdown(socket_client, SHUT_WR);
	close(socket_client);
	return EXIT_SUCCESS;	
}
