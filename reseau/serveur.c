#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

#define TAILLE 100
#define PORT 9600

int main(int argc, char *argv[]){
	int sock, acc;
	int taille_client, n;
	struct sockaddr_in adresse_serveur;
	struct sockaddr_in adresse_client;
	struct hostent * hote;
	char buf[TAILLE];
	char *nom_hote;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("erreur socket");
		exit(-1);
	}
	bzero((char *)&adresse_serveur, sizeof(adresse_serveur));
	adresse_serveur.sin_family = AF_INET;
	adresse_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
	adresse_serveur.sin_port = htons(PORT);
	if(bind(sock, (struct sockaddr *)&adresse_serveur, sizeof(adresse_serveur)) < 0){
		perror("erreur bind");
		exit(-1);
	}	
	if(listen(sock, 5) < 0){
		perror("erreur listen");
		exit(-1);
	}	
	taille_client = sizeof(adresse_client);
	while(1){
		if(acc = accept(sock, (struct sockaddr *)&adresse_client, &taille_client) < 0){
			perror("erreur accept");
			exit(-1);
		}
		if(hote = gethostbyaddr((const char *)&adresse_client.sin_addr.s_addr, sizeof(adresse_client.sin_addr.s_addr), AF_INET) == NULL){
			perror("erreur host");
			exit(-1);
		}
		if(nom_hote = inet_ntoa(adresse_client.sin_addr) == NULL){
			perror("erreur inet_ntoa");
			exit(-1);
		}
		printf("Connexion etablie avec %s (%s)\n",hote->h_name, nom_hote);
		bzero(buf, TAILLE);
		if(n = read(acc, buf, TAILLE) < 0){
			perror("erreur lecture");
			exit(-1);
		}
		printf("Le serveur a recu %d octets : %s", n, buf);
		if(n = write(acc, buf, strlen(buf)); < 0){
			perror("erreur écriture");
			exit(-1);
		}
		close(acc);
	}
}
