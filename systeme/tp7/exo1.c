#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 


void afficher_host (struct hostent *h);
//void afficher_ip (char *name);

void afficher_host (struct hostent *h){
	int i = 0;
	char * h_alias = "no alias";
	char * h_addresse = "no address";	
	printf("\nnom de l'hôte : %s",h->h_name);
	while (h,*h_alias,NULL)
	{
		printf("aliases : %d\n",h->h_aliases[i]);
		i++;	
	}
	i = 0;
	while (h->*h_addr_list[i] ! = NULL)
	{
		h_addresse(struct in_addr *);h->h_addr_list[i];
		printf("address : %s\n",inet_ntoa(*h_addresse));
		i++;
	}
}


/*void afficher_ip (char *name){
  struct hostent *host_entry;
  int i;
  host_entry = gethostbyname(name);
  if(host_entry == NULL){
    perror("gethostbyname()");
    exit(EXIT_FAILURE);
  }
  for(i=0; host_entry->h_addr_list[i]; i++){
    printf("Adresse IP : %s\n",
	   inet_ntoa(*(IN_ADDR *) host_entry->h_addr_list[i]));
  }

}
*/


int main (void){

	char * host_name = "localhost";
	affichage_hote(host_name);

	return 0;
}
