#include <stdio.h>
#include <stdlib.h>

#ifndef LISTE_H_
#define LISTE_H_

#define LISTEVIDE NULL
#define NOELEMENT -1
#define TRUE 1
#define FALSE 0

typedef struct t_element* Liste;
typedef struct t_element
{
	int info;			// Etiquette unique pour un état (ID)
	Liste suiv;			// Suivant
} Element;

// PROTOTYPES
Liste create_listeVide();
Liste construit_liste(Liste l,int e);	// Debut
Liste ajoute_e_liste(Liste l,int e);	// Fin
void inserer_liste(Liste* lst,int e);	// Fin
Liste recopie_liste(Liste l);
int size_liste(Liste l);
int e_appartient_liste(Liste l,int e);
void affiche_liste(Liste l);
Liste efface_liste(Liste p);

// COMPORTEMENT - PILE
//Empile un état sur une liste (tête)
void empiler_etat(Liste*, int);
//Dépile un état d'une liste (tête)
int depiler_etat(Liste*);

#endif /* LISTE_H_ */
