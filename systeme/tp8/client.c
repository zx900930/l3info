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

	int sock;
	struct sockaddr_in adresse_client, adresse_serveur;
	struct hostent* info;
	if(argc < 3){
		fprintf(stderr ,"Pas assez d'argument\n");
		exit(-1);
	}	
	info = gethostbyname(argv[1]);
	sock = creer_socket(SOCK_STREAM, argv[2], &adresse_client);
	adresse_serveur.sin_family = AF_INET;
	adresse_serveur.sin_port = htons(atoi(argv[2]));
	memcpy(&adresse_serveur.sin_addr.s_addr, info->h_addr, info->h_length);
	if(connect(sock, (struct sockaddr *)&adresse_serveur, sizeof(adresse_serveur))== -1){
		exit(-1);
	}
	printf("Lancer le service\n");
	//client_service(sock);
	return EXIT_SUCCESS;
}
