/* tcpserver.c */

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
#include"diffcomm.h"
#include"audioSD.h"
#include <signal.h>

//numero de port
#define PORT 5000
//fonctions utilisateur
//static void clean (char *chaine);
//static void purger(void);


int main()
{

	//sock pour la creation de la socket d'écoute
	//bytes_rcv pour le nombre de bytes recus
	//Et true c'est pour la liberation de l'adresse IP
	int sock, bytes_recieved , true = 1;  
	//socket du fils
	int connected = 0;
	//Les buffers de communication.
	char send_data [10024] , recv_data[10024];   
	//Les deux structures pour le client/serveur    
	struct sockaddr_in server_addr,client_addr;    
	//pour la taille	
	size_t sin_size;
        
	//creation de le socket
	//AF_INET protocole TCP/IP
	//SOCK_STREAM si on utilise le protocole TCP/IP
	// 0 = c lordi qui choisi ...
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}

	//liberer l'IP
	if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
		perror("Setsockopt");
		exit(1);
	}
    
	//on rempli la structure du serveur
	server_addr.sin_family = AF_INET;         
	server_addr.sin_port = htons(PORT);     
	server_addr.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(server_addr.sin_zero),8); 

	//on associe l'adresse a la socket
	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
		perror("probleme bind\n");
		exit(1);
	}

	//on met la socket en ecoute jusqu'a 5 connexions
	if (listen(sock, 5) == -1) {
		perror("Listen");
		exit(1);
	}
	//on indique qu'on attend des connections
	printf("TCPServer Attend une nouvelle connection sur le port 5000\n");

	fflush(stdout);
	

	while(1)
	{  

		sin_size = sizeof(struct sockaddr_in);
		//On accepte une connection puis on va créer un fils qui va s'occuper de ce client
		//et le serveur lui treviens a l'écoute d'une nouvelle connection 
		connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
		
		if (connected >0) 
		{

			//Variable pour le fork
			pid_t pid;
			//Creation d'un fils
			pid = fork();
            		//Si le fork a échoué on quitte
			if (pid == -1) {
                
				fprintf(stderr,"Erreur du fork\n");
				exit (-1);
			}

			//Code que va éxécuter le fils
			if (pid == 0) 
			{
				//On indique qu'il y a une nouvelle connection puis on lui envoi la liste de ce que le serveur possède
				//et on va se mettre a l'écoute du client afin d'éxécuter ses demandes
				fprintf(stderr,"\nNouvelle connection (%s , %d)\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
				int i,j;
				char contennu[100]= {0};
				char contenu2[100][100];
				for(i=0;i<100;i++)
				{
					for(j=0;j<100;j++)
					{
						contenu2[i][j]=0;
					}
				}
				//Ici on ouvre le fichier contenant la musique afin d'envoyer les titres
				DIR *dir;
				struct dirent *p;
				char *fic = NULL;

				dir=opendir("./Liste");
				int k=0;

				while((p = readdir(dir))!=NULL)
				{

					fic = p->d_name;

					strcpy(contennu,fic);
										

					if(strstr(contennu, ".ogg"))
					{
						sleep(1);
						send(connected, contennu,strlen(contennu), 0);
						printf("envoi de : %s\n",contennu);
						strcpy(contenu2[k],contennu);
						k++;
					}
					contennu[0]='\0';
				}
				strcpy(contennu,"FIN");
				send(connected, contennu,strlen(contennu), 0);
				closedir(dir);

				char * c="Vous êtes mantenant connecté au serveur\n";
		        	send(connected, c, strlen(c),0);
				


				//Cette boucle va communiquer avec le client jusqu'a la fin de la connection
				//C'est ici que les demandes seront éxécutées part ce fils
				while (1)
				{

				        //on ecoute skon nous envoi
				        bytes_recieved = recv(connected,recv_data,1024,0);
				        //on met la fin de chaine
				        recv_data[bytes_recieved] = '\0';


				        /************************** help *******************************/
				        
				        if (strcmp(recv_data , "help") == 0 ){
				            
						help(send_data, connected); 
					printf("1%s\n",recv_data);
				        }

				        /************************** decoder *******************************/
					else if (strstr(recv_data , ".ogg") != 0 ){
						int l=0;
						while(l<k)
						{
							if(strcmp(recv_data , contenu2[l]) == 0)
							{
								//pid_t rick;
								//rick=fork();

								//if(rick == 0)
								//{
								//	while(1){
								//		printf("appel a decoder\n");
										decoder(connected,recv_data,contenu2[l]);
								//	}
								//}
								//else 
								//{
									//on ecoute skon nous envoi
								//	bytes_recieved = recv(connected,recv_data,1024,0);
									//on met la fin de chaine
								//	recv_data[bytes_recieved] = '\0';
									
								//	if (strstr(recv_data , "stop") == 0 )
								//	{
								//		kill(rick, SIGKILL);
								//	}
									//strcpy(send_data,"******* Tansfer arreté ********");
								      	//send(connected, send_data, strlen(send_data),0);
								//}
							}
							l++;
						}
						
				        }


		      		        /************************** quitter serveur *******************************/
				        
				        //si on a recu q ou Q le serveur indique que le client a quitter
				        //et se remet en ecoute d'un nouveau client
				        else if (strcmp(recv_data , "quitter serveur") == 0)
				        {					
						quitter_client(connected, client_addr);
						break;
				        }
		                
				        /********************* affichage data recue ************************/
				        
				        //sinon on a pas recu q ou Q on affiche skon a recu
				        //et on revien au debu en haut
				        else
					{	
						affichage(send_data, connected);
					}		
				}

		            
		            
			}
		}     
	}  
    
	close(sock);
	//fclose(fichier);
	return 0;
} 

//au debut mon serveur parlait mais j'ai préferé le mettre juste a l'écoute


/*

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

*/
