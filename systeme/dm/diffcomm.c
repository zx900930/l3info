#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include "diffcomm.h"


//On envoi la liste des commandes reconnues
void help(char send_data[], int connected){

	strcpy(send_data,"******* Les commandes reconnues sont *******\n\n==> 'quitter serveur'pour quitter le serveur\n==>'liste musique' pour lister les musiques\n==>'jouer' pour jouer une musique\n==>'stop' pour stoper une lecture\n\n");
	send(connected, send_data,strlen(send_data), 0);

}

//Cette fonction c'est le serveur qui l'utilise afin de faire la liste des musiques présentes
void liste(int connected){

	char contennu[100]= {0};
	DIR *dir;
	struct dirent *p;
	char *fic = NULL;

	dir=opendir("./Liste");

	while((p = readdir(dir))!=NULL)
	{                
		fic = p->d_name;
		strcpy(contennu,fic);

		if(strstr(contennu, ".ogg"))
		{
			strcat(contennu,"\n");

			send(connected, contennu,strlen(contennu), 0);
		}
		contennu[0]='\0';
	}
	strcpy(contennu,"****** VOUS AVEZ REÇU LA LISTE MUSICALE *******\n");
	send(connected, contennu,strlen(contennu), 0);

	closedir(dir);
                   
}

//Si le serveur a reçu ça on quitte
void quitter_client(int connected, struct sockaddr_in client_addr){

	printf("Le client s'est deconnecter (%s , %d)\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
	close(connected);


}
//Si le serveur n'a pas reconnu ce que le serveur a envoyé il indique qu'il est à l'écoute
void affichage( char send_data[], int connected){

	strcpy(send_data,"******* Le serveur vous ecoute *******\n");
	send(connected, send_data,strlen(send_data), 0); 
	fflush(stdout);

}

