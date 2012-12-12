/*	Ce programme prend en entrée un ensemble de fichiers C
	 à compiler.
*/		

/******************************************  Liste des bibliothèques nécessaires     ***************************************** */ 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include <fcntl.h>

/******************************************          Fonction principale            ****************************************** */

int main (int argc, char* argv[]){


	int i; /* Variable de boucle */

	char * commande; /* "commande" est une variable de type "char" qui va servir à stocker la commande a éxécuter*/

	/* La variable "test" sert a garder le nom du fichier passé en paramètre
	afin de donner le même nom a l'executable une fois le fichier compilé. */
	char* test; 
	
	/* La variable "taille va permettre de stocker la longueur de la chaine de caractères qui compose le nom du fichier à compiler*/		
 	int taille;

	/* Variable pour tester si on peut créé les .o */
	int file; 

	/* Variable pour tester la présence du compilateur */
	int compl;

	/* On teste la présence du compilateur */
	compl = open("/usr/bin/gcc",O_RDONLY);
	if(compl < -1){
		fprintf(stderr, "Pas de compilateur\n");
		exit(-1);
	}

	/* On teste si il y a au moins un fichier à compiler, sinon on quitte*/
	if(argc <= 1){
		fprintf(stderr, "Pas de fichier à compiler\n");
		exit(-1);
	}

	/* Tant qu'il y a des fichiers à compiler... */
	for(i=1; i<argc; i++){
		/* On teste l'existence des fichiers passés en argument*/
		if(fopen(argv[i], "r") == NULL){
			fprintf(stderr, "Le fichier %s n'existe pas\n", argv[i]);	
		}
		else{
			/*... on alloue la mémoire nécessaire à la variable commande... */
			commande = (char*) malloc((strlen("gcc -Wall -o ") + strlen(argv[i]) +1) + strlen(argv[i] -2)*sizeof(char));

			/* ...on concatène les éléments de la commande un par un dans la variable commande */
			strcat(commande, "gcc -Wall "); 
			strcat(commande, argv[i]); 
			strcat(commande, " -o ");

			/* Cette partie sert à indiquer le nom du fichier exécutable */
			taille = strlen(argv[i]); 

			/* On alloue à test la mémoire nécessaire */
			test = (char*)malloc(sizeof(char*)*(taille-2));

 			/* dans la variable test, on copie la chaîne de caractère qui compose le ficher .c
			 sans le ".c" à la fin (ex: test1.c devient test1) */
			strncpy (test, argv[i], taille - 2); 
			strcat(commande, test);

			/* on lance la commande system et on teste si elle a fonctionné */
			if(system(commande) == -1){ 
				perror("probleme systeme");
			}

			/* On teste si l'éxécutable a été créé */
			file = open(test, O_RDONLY);
			if(file > -1){
				/* Pour générer les .o on relance la commande system avec "commande" */
				free(commande); 
				commande = (char*) malloc((strlen("gcc -c -Wall ") + strlen( argv[i] +1))*sizeof(char));
				strcat(commande, "gcc -c -Wall ");
				strcat(commande, argv[i]);

				if(system(commande) == -1){
					perror("Problème fonction systeme.\n");
					exit(-1);
				}
			}

			/* on libère la mémoire alloué à commande */
			free(commande); 
			free(test);
		}
	}

	

	return EXIT_SUCCESS;
}
