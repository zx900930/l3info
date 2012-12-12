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

/*Création socket de type "type" de domaine AF_INET avec le port et l'adresse de la machine
ou sera attachée la socket*/
int creer_socket(int type, int port, SOCKADDR_IN *prt_adresse){

	/*Création de la socket*/
	SOCKET sock;
	sock = socket(AF_INET, type, 0);

	/*Parametrer socket*/
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;//internet
	sin.sin_port = port;//numéro port associé
	sin.sin_addr.s_addr = htons(INADDR_ANY);//socket associé à une des adresse de la machine
						    //conversion adresse host en network	
	/****connexion avec le client****/
	/*association des info à la socket*/
	bind(sock, (SOCKADDR*)&sin, sizeof(sin));

	/*récupération du nom de la machine*/
	getsockname(sock, (SOCKADDR*)prt_adresse, (size_t)sizeof(SOCKADDR));
	/*On obtient dans "prt_adresse" le port et la machine du client*/

	return sock;
}

void client_service(SOCKET socket){
	char buf[200];
	int taille;
	while(1){
		read(socket, &taille, sizeof(int));
		read(socket, buf, taille);
	}
}

