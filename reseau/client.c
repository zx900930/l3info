#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define TAILLE 100
#define PORT 9600

int main(int argc, char **argv){
	if(argc != 2){
		fprintf(stderr,"usage: %s <hostname>\n",argv[0]);
		exit(0);
	}
	int sockfd, n;
	struct sockaddr_in serveraddr;
	struct hostent * server;
	char *hostname;
	char buf[TAILLE];
	
	if(sockfd = socket(AF_INET, SOCK_STREAM, 0) < 0){
		perror("erreur socket");
		exit(-1);
	}
	hostname = argv[1];
	if(server = gethostbyname(hostname) == NULL){
		perror("erreur nom d'hote");
		exit(-1);
	}
	
	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,(char *)&serveraddr.sin_addr.s_addr, server->h_length);
	serveraddr.sin_port = htons(PORT);

	if((connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))) < 0){
		perror("erreur connection");
		exit(-1);
	}
	
	printf("Entrez un message: ");
	bzero(buf, TAILLE);
	fgets(buf, TAILLE, stdin);
	if(n = write(sockfd, buf, strlen(buf)) < 0){
		perror("erreur écriture");
		exit(-1);
	}
	
	bzero(buf, TAILLE);
	if(n = read(sockfd, buf, TAILLE) < 0){
		perror("erreur lecture");
		exit(-1);
	}
	printf("Reponse du serveur : %s", buf);
	close(sockfd);
	return 0;
}
