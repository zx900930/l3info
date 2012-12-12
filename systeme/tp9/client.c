#include "socket.h"
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<netinet/in.h>

int main(int argc, char* argv[]){
	struct hostent* hp;//Pour les info de la machine serveur
	SOCKADDR_IN adresse_client;
	hp = gethostbyname(argv[1]);//récuperation du nom du serveur
	int port=1200;
	/*Création socket client*/
	SOCKET socket_client;
	socket_client = creer_socket(SOCK_STREAM, port, &adresse_client);
	/*Parametre socket serveur*/
	SOCKADDR_IN adresse_serveur;
	adresse_serveur.sin_family = AF_INET;
	adresse_serveur.sin_port = htons(atoi(argv[2]));//port utilisé
	memcpy(&adresse_serveur.sin_addr.s_addr, hp->h_addr, hp->h_length);//adresse IP du serveur
	/*Etablir connexion avec serveur*/
	if(connect(socket_client,(SOCKADDR*)&adresse_serveur,sizeof(adresse_serveur))==-1){
		exit (-1);
	}
	printf("Lancer le service\n");
	client_service(socket_client);
	
	return 0;
}
