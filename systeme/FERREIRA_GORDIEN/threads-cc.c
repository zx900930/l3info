/*	Ce programme prend en entrée un ensemble de fichiers C
	 crée un thread par fichier à compiler et le thread compile le fichier
*/		


/******************************************  Liste des bibliothèques nécessaires     ***************************************** */ 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/types.h>
#include <fcntl.h>


/***************************************** Déclaration de fonctions type utilisateur ***************************************** */
void fonction(char *);
 

/******************************************          Fonction principale            ****************************************** */
int main(int argc, char *argv[]){

	int i;	/* Variable de boucle */

 	/* Tableau de threads dont la taille est le nombre d'arguments passés en paramètres */
	pthread_t thread[argc];

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

 	/* Boucle qui créé les threads, et leur donne la fonction "fonction" a éxécuter */
	for(i=1 ; i<argc ; i++){
		/* On teste l'existence des fichiers passés en argument*/
		if(fopen(argv[i], "r") == NULL){
			fprintf(stderr, "Le fichier %s n'existe pas\n", argv[i]);	
		}
		/* On teste si les threads on bien été créés 
		   dans le cas contraire, on quitte le programme en affichant un message d'erreur */
		else if(pthread_create(&thread[i-1], NULL, (void *)fonction, argv[i]) == -1){
			fprintf(stderr, "Erreur à la création du thread");
			exit(-1);
		}
		else{
			/*On attend la fin de l'éxécution de chaque thread. */
			pthread_join(thread[i-1], NULL);
		}
	}

	return EXIT_SUCCESS;
}

/***************************************** Définition de fonctions type utilisateur ***************************************** */

/*Cette fonction est executé par chaque thread créé.
  Elle prend un argument passé en paramètre (fichier.c) et le compile.
*/
void fonction(char *nom_fichier){
	/* "commande" est une variable de type "char" qui va servir à stocker la commande a éxécuter*/
	char *commande;	
 
	/* La variable "test" sert a garder le nom du fichier passé en paramètre
	afin de donner le même nom a l'executable une fois le fichier compilé. */
	char* test;	

	/* La variable "taille va permettre de stocker la longueur de la chaine de caractères qui compose le nom du fichier à compiler*/		
	int taille;	

	/* Variable pour tester si on peut créé les .o */
	int file; 

	/*On alloue la taille nécessaire à la variable "commande" */
	commande = (char*) malloc((strlen("gcc -Wall -o ") + strlen(nom_fichier) +1) + strlen(nom_fichier -2)*sizeof(char));

	/*On affecte à la variable "commande" les éléments de la commande à éxécuter */ 	
	strcat(commande, "gcc -Wall ");
	strcat(commande, nom_fichier);
	strcat(commande, " -o ");

	/* Cette partie sert à indiquer le nom du fichier exécutable */
	taille = strlen(nom_fichier);

	/*On alloue la taille nécessaire à la variable "test" */
	test = (char*)malloc(sizeof(char*)*(taille-2));

	/*Dans la variable test, on copie la chaîne de caractère qui compose le ficher .c, sans le ".c" à la fin (ex: test1.c devient test1) */
	strncpy (test, nom_fichier, taille - 2);

	/*On affecte à "commande" le nom du fichier de l'éxécutable */
	strcat(commande, test);

 	/*On éxécute la commande "system" et on teste si elle s'est bien éxécuté */
	/* Si elle ne s'est pas bien éxécuté, on quitte le programme */
	if(system(commande) == -1){
		perror("Problème lors de la compilation\n");
		exit(-1);
	}

	/* On teste si l'éxécutable a été créé */
	file = open(test, O_RDONLY);
	if(file > -1){
		/* Pour générer les .o on relance la commande system avec "commande" */
		free(commande); 
		commande = (char*) malloc((strlen("gcc -c -Wall ") + strlen(nom_fichier +1))*sizeof(char));
		strcat(commande, "gcc -c -Wall ");
		strcat(commande, nom_fichier);

		if(system(commande) == -1){
			perror("Problème fonction systeme.\n");
			exit(-1);
		}
	}
	/*On libère toute la mémoire alloué précedemment */
	free(commande);
 	free(test);
}


