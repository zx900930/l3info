#include "client.h"

int creer_socket(int type, int *ptr_port, char *adresse, struct sockaddr_in *ptr_adresse){
	int s;

	ptr_adresse->sin_family = AF_INET;
	ptr_adresse->sin_port = htons(*ptr_port);
	ptr_adresse->sin_addr.s_addr = htonl(atoi(adresse));

	if((s = socket(AF_INET, type, 0)) == -1){
		perror("erreur creation socket");
		exit(EXIT_FAILURE);
	}

	if((bind(s, (struct sockaddr *)ptr_adresse, sizeof(*ptr_adresse)) == -1)){
		perror("erreur bind");
		exit(EXIT_FAILURE);
	}

	return s;
}


void client_lit_stdin(int socket){
	char *message = NULL;
	int taille;
	
	if((read(socket, &taille, sizeof(int))) < 0){
		perror("read");
		exit(EXIT_FAILURE);
	}
	
	if((read(socket, message, taille)) < 0){
		perror("read");
		exit(EXIT_FAILURE);
	}
	
	printf("%s\n", message);
}

int main(int argc, char **argv){
	struct sockaddr_in serveur_addr;
	struct hostent *h;
	int sd, serveur_port;

	if((h = gethostbyname(argv[1])) == NULL){
		perror("gethostbyname");
		exit(EXIT_FAILURE);
	}
	serveur_port = atoi(argv[2]);
	serveur_addr.sin_family = AF_INET;
	serveur_addr.sin_port = htons(atoi(argv[2]));
	//serveur_addr.sin_addr = (struct in_addr *)h->h_addr_list[0];
	memcpy(&serveur_addr.sin_addr.s_addr, h->h_addr, h->h_length);

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	if(connect(sd, (struct sockaddr *)&serveur_addr, sizeof(serveur_addr)) < 0){
		perror("connect");
		exit(EXIT_FAILURE);
	}

	client_lit_stdin(sd);

	return EXIT_SUCCESS;
}
