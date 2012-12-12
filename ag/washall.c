#include"washall.h"
#include<stdio.h>

int adjacent(int n1,int n2, grapheMa *pg){
	return pg->tab[n1][n2];
}

void addArc(int n1,int n2,grapheMa *pg, int val){
	pg->tab[n1][n2]=val;
}

void addEdge(int n1,int n2,grapheMa *pg, int val){
	addArc(n1,n2,pg,val);
	addArc(n2,n1,pg,val);
}

void affichegrapheMa(grapheMa *pg){
	int sommet;
	sommet = pg->n;
	int i=0;
	int j;	

	while(i<sommet){
		for(j=0;j<sommet;j++){
			if(adjacent(i,j,pg)>0){
				printf("il y a un arc entre %d et %d \n",i,j);
			}
		}
		i++;	
	}
}

int degre(grapheMa * pg, int s){
	int i, degre = 0;
	for (i = 0; i < pg->n; i++){
		if (pg->tab[s][i] == 1){
			degre = degre + 1;
		}
	}
	return degre;
}

int degreExterieur(grapheMa * pg, int s){
	int i, degre = 0;
	for (i = 0; i < pg->n; i++){
		if (pg->tab[s][i] == 1){
			degre = degre + 1;
		}
	}
	return degre;
}

int degreInterieur(grapheMa * pg, int s){
	int i, degre = 0;
	for (i = 0; i < pg->n; i++){
		if (pg->tab[i][s] == 1){
			degre = degre + 1;
		}
	}
	return degre;
}

int successeur(grapheMa* pg, int a, int b){
	while(b<pg->n && pg->tab[a][b]==0){
		b++;
	}
	return b;
}

void warshall (grapheMa* pg, grapheMa* pgt){
	int i, j, k;	
	pgt->n = pg->n;
	for(i = 0; i < pgt->n-1; i++){
		for(j = 0; j < pgt->n-1; j++){
			pgt->tab[i][j] = pg->tab[i][j];
		}
	}
	for(k = 0; k < pgt->n-1; k++){
		for(i = 0; i < pgt->n-1; i++){
			for(j = 0; j < pgt->n-1; j++){
				pgt->tab[i][j] = pgt->tab[i][j] || (pgt->tab[i][k] && pgt->tab[k][j]);
			}
		}
	}
}

void init_grapheMa(grapheMa* pg){
	int i, j;
	for(i = 0; i < pg->n-1; i++){
		for(j = 0; j < pg->n-1; j++){
			pg->tab[i][j] = N;
		}
	}
}

int somme(int listeSommets[], int n){

	int i, s;
	s = 0;
	for(i = 0; i<n; i++){
		s = s + listeSommets[i];
	}
	return s;
}




























