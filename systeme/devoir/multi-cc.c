#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


int main (int argc, char* argv[]){

	int i;
	char * commande;
	char* test;
	int taille;
	if(argc <= 1){
		fprintf(stderr, "Pas de fichier à compiler\n");
		exit(-1);
	}
	for(i=1; i<argc; i++){		
		commande = (char*) malloc((strlen("gcc -Wall -o ") + strlen(argv[i]) +1) + strlen(argv[i] -2)*sizeof(char));
		strcat(commande, "gcc -Wall ");
		strcat(commande, argv[i]);
		strcat(commande, " -o ");	
		taille = strlen(argv[i]);
		test = (char*)malloc(sizeof(char*)*(taille-2));
		strncpy (test, argv[i], taille - 2);
		strcat(commande, test);
		printf("%s\n", commande);
		if(system(commande) == -1){
			perror("probleme systeme");
		}
	}	
	free(commande);
	return EXIT_SUCCESS;
}
