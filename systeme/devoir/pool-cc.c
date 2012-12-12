/* Ce programme lance deux threads qui vont compiler 

/******************************************  Liste des bibliothèques nécessaires     ***************************************** */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<sys/types.h>

/***************************************** Déclaration de fonctions type utilisateur ***************************************** */
void * fonction(void * arg);
void prologue(int self);
void epilogue(int self);


/*****************************************      Déclaration de variables globales    ***************************************** */

char** tab;		/* "tab" est une variable qui va servir à stocker les arguments passés en paramètres */
pthread_t thread[2];	/* Tableau de deux threads */
int nb_arg;		/*Nombre de fichiers à compiler */
int k = 1;		/* Variable de boucle */
int flag[2], turn;	/* Variables qui vont permettre les exclusions mutuelles entre les threads. */


/******************************************          Fonction principale            ****************************************** */
int main(int argc, char **argv){

	int i;	/* Variable de boucle. */
	
	/* On teste s'il y a au moins un fichier passé en paramètre à fin de le compiler 
	   s'il n'y en à pas on affiche un message pour le signaler. */
	if(argc <= 1){
		fprintf(stderr, "Pas de fichier à compiler\n");
		exit(-1);
	}

	/* On affecte a "tab" tous le contenu de argv. */
	tab = argv;

	/* On affecte a "nb_arg" le nombre de fichiers à compiler */
	nb_arg = argc - 1;

	/* Boucle qui créé les threads, et leur donne la fonction "fonction" a éxécuter */
	for(i = 0; i < 2; i++){
		/* On teste si les threads on bien été créés 
		   dans le cas contraire, on quitte le programme en affichant un message d'erreur */
		if(pthread_create(&thread[i],NULL, fonction, (void*)i) == -1){
			fprintf(stderr, "Erreur à la création du thread\n");
			exit(-1);
		}
	}

 	/*On attend la fin de l'éxécution de chaque thread. */
	for(i=0 ; i < 2; i++){
		pthread_join(thread[0], NULL);
	}
	return EXIT_SUCCESS;
}

/***************************************** Définition de fonctions type utilisateur ***************************************** */


/* Cette fonction permet de bloquer tous les threads sauf un qui lui, aura accès à la section critique. */
void prologue(int self){
	flag[self] = 1;
	turn =! self;
	while(flag[!self] && turn == !self);
}

/* Cette fonction permet de passer la main à un des threads en attente pour entrer en section critique. */
void epilogue(int self){
	flag[self] = 0;
}


/*Cette fonction est executé par les deux thread créé.
  Elle prend en argument le numéro du thread.
  Chaque thread, en compilant un argument stocké dans le tableau, consomme cette entré
  et y met la valeur NULL afin que le deuxième thread ne recompile ce dernier. 
*/
void * fonction(void * arg){

	/* "commande" est une variable de type "char" qui va servir à stocker la commande a éxécuter*/
	char* commande;

	/* La variable "taille va permettre de stocker la longueur de la chaine de caractères qui compose le nom du fichier à compiler*/		
	int taille;

	/* La variable "test" sert à garder le nom du fichier passé en paramètre
	afin de donner le même nom a l'executable une fois le fichier compilé. */
	char* test;

	/* Tant qu'on à pas compiler tout les fichiers passés en paramètres */ 
	while(k <= nb_arg){

		/*On bloque l'un des threads pour qu'ils ne complilent pas le même fichier. */
		prologue((int) arg);

		/* On teste si l'iterateur globale à depasser le nombre d'arguments */
		if(k > nb_arg){
			exit(0);
		}
		printf("\nJe suis le thread num %d, et je consomme le fichier %s\n\n", (int) arg, tab[k]);

		/*On alloue la taille nécessaire à la variable "commande" */
		commande = (char*) malloc((strlen("gcc -Wall -o ") + strlen(tab[k]) +1) + strlen(tab[k] -2)*sizeof(char));
		strcat(commande, "gcc -Wall ");
		strcat(commande, tab[k]);
		strcat(commande, " -o ");

		/* Cette partie sert à indiquer le nom du fichier exécutable */
		taille = strlen(tab[k]);
		test = (char*)malloc(sizeof(char*)*(taille-2));
		strncpy (test, tab[k], taille - 2);
		strcat(commande, test);

		/* on lance la commande system et on teste si elle a fonctionné */
		if(system(commande) == -1){
			perror("Problème fonction systeme.\n");
			exit(-1);
		}

		/* Une fois un fichier compiler, on le supprime du tableau en y insérent NULL */
		tab[k]=NULL;

		/*On libère toute la mémoire alloué précedemment */
		free(commande);
		free(test);
		k++;
		/* On passe la main pour la prochaine itération. */
		epilogue((int) arg);
	}
	return (0);
}

