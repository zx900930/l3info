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
	SOCKADDR_IN adresse;//client
	int port;
	SOCKET socket_ecoute, socket_service;
	port = atoi(argv[1]);
	socket_ecoute = creer_socket(SOCK_STREAM, port, &adresse);
	listen(socket_ecoute,5);

	while(1){
		printf("\nAttente connection...\n");
		/*Acceptation d'une connexion pendante*/
		socket_service = accept(socket_ecoute,(SOCKADDR*)&adresse,sizeof(SOCKADDR_IN));
		printf("\nNouvelle connection\n");

		if(fork() == 0){
			close(socket_ecoute);
			client_service(socket_service);
		}

		close(socket_service);
	}
	return 0;
}
