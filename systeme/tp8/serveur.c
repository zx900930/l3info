#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char * argv[]){

	struct sockaddr_in adresse;
	int port;
	int socket_ecoute, socket_service;

	port = atoi(argv[1]);
	socket_ecoute = creer_socket(SOCK_STREAM, &port, &adresse);
	listen(socket_ecoute, 10);
	while(1){
		printf("Attente connection\n");
		accept(socket_ecoute, (struct sockaddr*)&adresse, sizeof(struct sockaddr_in));
		printf("Nouvelle connection\n");
		if(fork() == 0){
			close(socket_ecoute);
			fonction_service(socket_service);
		}
	close(socket_service);
	return EXIT_SUCCESS;
}
