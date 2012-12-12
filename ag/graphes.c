#include <stdio.h>
#include "graphes.h"


/* principale */
int main(){
	int i, j;
	graphe g;
	g.n=4;
	int pere[g.n];
	int lambda[g.n];
	/*initialiser graphe*/
	graphe_init(&g);	

	addArc(0,1,&g,2);
	addArc(0,2,&g,3);
	addArc(1,4,&g,7);
	addArc(2,4,&g,8);

	affiche(&g);
	/*dfsx0
	dfsx0(&g, &x0, &suffixe[]);*/
	/*explore
	explore(&g, &x, &marque[MAX_VERTEX_NUM], &suffixe[MAX_VERTEX_NUM], &k);
	*/
	Dijkstra(&g, 0, pere, lambda);
	printf("\n\n\n");
	for(i =0; i<3; i++){
		printf("père de %d:%d et lambda :%d\n",i,pere[i],lambda[i]);
	}
	return 0;
}

/* fonctions */ 
int adj(int n1,int n2, graphe *pg){
    return pg->tab[n1][n2];
}

void addArc(int n1,int n2,graphe *pg, int valeur){
    pg->tab[n1][n2]=valeur;
}

void addEdge(int n1,int n2,graphe *pg, int valeur){
    addArc(n1,n2,pg,valeur);
    addArc(n2,n1,pg,valeur);
}

void affiche(graphe *pg){
    int sommet;
    sommet = pg->n;
    int i=0;	
    int j;
    while(i<sommet){
	for(j=0;j<sommet;j++){
	    if(adj(i,j,pg)>0){
		printf("arc: %d et %d \n",i,j);
	    }
	}
	i++;	
    }
}

int successeur(graphe* pg, int i, int j){
	while(j<pg->n && pg->tab[i][j]==0){
		j++;
	}
	return j;
}

void graphe_init(graphe* pg){
	int i, j;
	for(i = 0; i < pg->n-1; i++){
		for(j = 0; j < pg->n-1; j++){
			pg->tab[i][j] = -INFINITY;
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

void dfsx0 (graphe *pg, int x0, int suffixe[]){

    int marque[MAX_VERTEX_NUM], k,j;
    for (j=0; j < pg->n; j++)
	marque[j]= 0;
    k=0;
    explore(pg,x0,marque,suffixe,k);
    return;
}


void explore(graphe *pg, int x, int marque[MAX_VERTEX_NUM], int suffixe[MAX_VERTEX_NUM], int k){
    int i;
    k=k+1;
    marque[x]=k;
    printf(" sommet %d \n",x);
    for (i=0;i< (*pg).n; i++) {// ou pg->n 
	//		 printf("fils ?  ?");
	if ( (*pg).tab[x][i] !=-INFINITY  && marque[i] ==0){

	    explore(pg, i, marque, suffixe, k);
	}
    }
    suffixe[x]=k;
}

void Dijkstra(graphe* pg, int i0, int p[], int lambda[]){
	int i, j;
	int s;
	int lambdamin;
	int listeSommets[MAX_VERTEX_NUM];
	p[i0] = -1;
	lambda[i0] = 0;
	for(i=0; i<pg->n; i++){
		lambda[i] = LMDMAX;
		listeSommets[i]=0;
	}
	listeSommets[i0]=1;
	lambda[i0]=0;
	i = i0;
	while(somme(listeSommets,pg->n)!=pg->n){
		j= successeur(i , -1, pg);
		printf("Premier successeur de %d = %d\n", i, j);
	while(j != -1){
		if(listeSommets[j] == 0){
			printf("->%d, courant lambda[%d] = %d\n", j, j, lambda[j]);
			printf("lambda[%d](%d) + val(%d -> %d)(%d) = %d\n", i, lambda[i], i, j, pg->tab[i][j], lambda[i] + pg->tab[i][j]);
			if(lambda[j]>lambda[i] + pg->tab[i][j]){
				lambda[j]=lambda[i] + pg->tab[i][j];
				p[j] = i;
				printf("->%d, nouveau labmda[%d] = %d\n", j, j, lambda[j]);
			}
		}
		j=successeur(i, j, pg);
	}
	printf("\n");
	lambdamin=1+pg->n*LMDMAX;
	i=-1;
	for(s=0; s<pg->n; s++){
		if(listeSommets[s] == 0 && lambda[s] < lambdamin){
			i=s;
			lambdamin=lambda[i];
		}
	}
	printf("On sélectionne le sommet %d de marque minimum lambda = %d\n", i, lambdamin);
	listeSommets[i]=1;	
	}
}

