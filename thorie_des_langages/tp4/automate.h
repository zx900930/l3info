#ifndef AUTOMATE_H
#include<stdio.h>
#include<stdlib.h>

typedef struct automate_s{
	int n; //nombre d'etat
	int k; //taille de l'alphabet, nb de lettres
	char *alpha; //tableau cointenant l'alphabet
	int *etats_term; //liste etats terminaux
	int **transition; 

}automate_t;

automate_t *creer_automate(int n, int k, char * al);
void rendre_etat_final(automate_t *a, int p); //etat p
int etat_est_final(automate_t *t, int p); //etat p
void init_transition(automate_t *t , int depart, int arrive, int lettre);
int arrive_transition(automate_t *t ,int depart,char lettre);	//renvoi l'arrivée de la transition 
void detruire_automate(automate_t *t);
void affiche_auto(automate_t *t);

#endif

