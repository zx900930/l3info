#include"grapheLA.h"
#include<stdio.h>
#include<stdlib.h>

/*int adjacent(int n1, int n2, grapheLa* pg){
	cellule *p;
	p = pg->tab[n1];
	while(p != NULL){
		if (p->noeud == n2) return 1;
		p = p-> psucc;
	}
	return 0;
}*/

void init(grapheLa *pg){
	int i;
	for(i=0;i<pg->n;i++){
		pg->tab[i] = NULL;
	}
}
void addArc(int n1,int n2,grapheLa *pg){
	cellule *p, *s;

	s = pg->tab[n1];
	p = malloc(sizeof(cellule));
	p->noeud = n2;
	p->psucc = s;
	pg->tab[n1] = p;
	
}

void addEdge(int n1,int n2,grapheLa *pg){
	addArc(n1,n2,pg);
	addArc(n2,n1,pg);
}

void afficheGraphe(grapheLa *pg){
	int sommet, i;
	sommet = pg->n;
	cellule *p;
	for(i = 0; i<sommet; i++){
		p = pg->tab[i];
		while(p != NULL){
			printf("Il y a un arc entre %d et %d\n", i, pg->tab[i]->noeud);
			p = p->psucc;
		}
		
	}
}
