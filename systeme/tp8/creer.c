#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>

int creer_socket(int type, int port, struct sockaddr_in *prt_adresse){
	int sock;
	struct sockaddr_in adresse;
	sock = socket(AF_INET, type, 0);
	adresse.sin_family = AF_INET;
	adresse.sin_port = htons(port);
	adresse.sin_addr.s_addr = htons(INADDR_ANY);
	bind(sock, (struct sockaddr*)&adresse, sizeof(struct sockaddr));
	getsockname(sock,(struct sockaddr*)prt_adresse, sizeof(struct sockaddr));
	return sock;
}


