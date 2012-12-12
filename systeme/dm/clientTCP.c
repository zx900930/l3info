/* tcpclient.c */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "audioCl.h"
#include <ao/ao.h>
#include <signal.h>

//Numero de port.
#define PORT 5000

/*
 *Fonctions utilisateurs.
*/
static void clean (char *chaine);
static void purger(void);

/*
 * Variable pour arreter une lecture
*/
int stop=0;

int main()
{

	/************************* Declarations de variables *****************************/
	//Descripteur de la socket.
	//int sock_fils;
	int sock;
	//Nombre de bytes reçus.
	int bytes_recieved;  
	//Buffers pour les échanges.
	char send_data[1024];
	char recv_data[1024]={0};
	//Structure qui contient les informations du serveur.
	struct hostent *host;
	//Structure d'adressage pour le serveur.
	struct sockaddr_in server_addr;
	//Tableau pour contenir les noms des pistes.
	char *son[1000]; 
	//Variables de boucles.
	int i=0;
	int piste=0;
	//Variable pour contenir le nombre de morceaux disponibles.
	int taille;
	//Variable pour une instruction.
	char *inst;

	//on recupere les infos du serveur
	host = gethostbyname("127.0.0.1");

	//on vrée la socket client
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("Socket");
	        exit(1);
	}

	 
    
	//on rempli les champs de la structure serveur
	server_addr.sin_family = AF_INET;     
	server_addr.sin_port = htons(PORT);   
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(server_addr.sin_zero),8); 

	//on connecte la socket client au serveur
	if (connect(sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1) 
	{
		perror("Connect");
		exit(1);
	}
	/************************** Liste musique *******************************/

	//message d'accueil pour le client
	//et on commence a recevoire le comptenu disponible chez le serveur
	printf("Vous recevez le contenu du serveur\n");
	bytes_recieved=recv(sock,recv_data,1024,0);
	//on met ça parceque c'est une chaine de caracteres(on le fera a chaque reception
	recv_data[bytes_recieved] = '\0';


	//tan qu'on à pas reçu tout le comptenu on boucle
	while(strcmp(recv_data,"FIN")!=0)
	{
		//on verifie que ce que le serveur nous envoi ce sont bien des noms de musiques au format ogg
		//puis on alloue de la memoire et on stocke les noms
		if(strstr(recv_data,".ogg"))
		{
			son[i]=malloc(sizeof(recv_data));
			strcpy(son[i],recv_data);
			i++;
		}
		bytes_recieved=recv(sock,recv_data,1024,0);
		recv_data[bytes_recieved] = '\0';
	}
	//on recupere dans taiile le nombre de morceaux disponibles
	taille=i;

	while(1)
	{



		//On est a l'ecoute
		bytes_recieved=recv(sock,recv_data,1024,0);
		recv_data[bytes_recieved] = '\0';
	
		//on affiche ce que le serveur nous a envoyé
		printf("\nDATA RECUE : %s" , recv_data);
		printf("Tapez 'help' pour obtenir de l'aide \n");
		//on recupere ce que l'utilisateur a taper
		fgets(send_data,sizeof(send_data),stdin);
		clean(send_data);

		/* On va faire des testes pour voir ce que desire l'utilisateur
		 * si on a pas compris sa demande on l'indique par un affichage 
		*/

			
		/************************** Quitter serveur **************************/

		if (strcmp(send_data , "quitter serveur") == 0)
		{
			send(sock,send_data,strlen(send_data), 0);   
			exit (-1);	
	    	}

		/************************** Liste des musiques du client **************************/

		else if (strcmp(send_data , "liste musique") == 0)
		{
			liste_musiques(son,taille);
			send(sock,send_data,strlen(send_data), 0);   	
	    	}

		/************************** demander une musique *******************************/
		else if (strcmp(send_data , "jouer") == 0)
		{
			printf("jouer quelle piste?(donner le chiffre correspondant à la musique désirée)\n");
			scanf("%d",&piste);
			while (piste>taille)
			{
				printf("numero incorrect\nréessayez :");
				scanf("%d",&piste);	 	
			}
			send(sock,son[piste-1],strlen(son[piste-1]), 0);   	

/*
			//on recoit les données
			pid_t pid22;
			pid22 = fork();
			if(pid22 < 0)
			{
				printf("ERREUR FORK\n");
				
			}
			send(sock,son[piste-1],strlen(son[piste-1]), 0);   	

			while(1)
				{
				printf("%s",recv_data);
					recv(sock,recv_data,strlen(recv_data),0);
					//strcat(buffer3,recv_data);
					ao_play(device, recv_data, sizeof(recv_data));


				}


			if(pid22 ==0)
			{

				//char buffer3[1024];
				//bzero(buffer3,10024);
				//recv(sock_fils,buffer3,strlen(buffer3),0);

				//while(!stop)
				//{
					recv(sock,recv_data,strlen(recv_data),0);
					//strcat(buffer3,recv_data);
					ao_play(device, recv_data, sizeof(recv_data));


				//}
				//exit (0);
			}
			else 
			{
				printf("tapper stop pour arreter la lecture\n");
				//on recupere ce que l'utilisateur a tappe
				scanf("%s",&inst);
				kill(pid22, SIGKILL);
				//stop=1;
				strcpy(send_data,"merci");
				send(sock,send_data,strlen(send_data), 0);  
				//kill(pid22, SIGKILL); 
			}
*/


				
		}

		/************************** Liste des musiques du client *******************************/
		else if (strcmp(send_data , "help") == 0)
		{
			send(sock,send_data,strlen(send_data), 0);   
	    	}

		/************************** autre *******************************/
		
		//si l'utilisateur a tapper q Q on quitte
		//on previen le serveur kon le quitte
		else{

			printf("************ ERREUR : message non reconnu ************\n");
			strcpy(send_data,"ERREUR");
			send(sock,send_data,strlen(send_data), 0);   

		}
	}
   	close(sock);
	return 0;
}



//cette fonction attend la fin de saisie du client
static void purger(void)
{
    int c;
    
    while ((c = getchar()) != '\n' && c != EOF)
    {}
}
//cette fonction met le 0 de fin de chaine a la place du retour a la ligne automatique de fgets
static void clean (char *chaine)
{
    char *p = strchr(chaine, '\n');
    
    if (p)
    {
        *p = 0;
    }
    
    else
    {
        purger();
    }
}

