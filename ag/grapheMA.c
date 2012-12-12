#include"grapheMA.h"
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

void afficheGraphe(grapheMa *pg){
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

/*void parcoursP(grapheMa* pg){
		
}*/

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

void init_graphe(grapheMa* pg){
	int i, j;
	for(i = 0; i < pg->n-1; i++){
		for(j = 0; j < pg->n-1; j++){
			pg->tab[i][j] = N;
		}
	}
}

/*void Dijkstra(grapheMa* pg,int i,int* pere,int* lambda){

	int k, m;
	//int S[pg->n];
	int a = i;
	for(k = 0; k < pg->n; k++){
		lambda[k]=LMAX;	
		pere[k]=(-1);
		//S[k]=0;
	}
	lambda[i]=0;
	while(a<pg->n){
		for(k=0;k<pg->n;k++){
			printf("bla%d\n",pg->tab[a][k]);
			if((pg->tab[a][k])>=0){
				printf("k, lambda, lambda pere%d,%d,%d\n",k,lambda[k],lambda[a]);
				for(m=0;m<pg->n;m++){
					printf("pere%d\n",pere[m]);
				}
				if((lambda[k]>lambda[a]+pg->tab[a][k])){
					printf("clu%d,%d,%d\n",lambda[a],pg->tab[a][k],a);
					lambda[k] = lambda[a] + pg->tab[a][k];
					pere[k] = a;
				}
			}
		}
	a++;
	}
}*/

int somme(int listeSommets[], int n){

	int i, s;
	s = 0;
	for(i = 0; i<n; i++){
		s = s + listeSommets[i];
	}
	return s;
}

void Dijkstra(grapheMa* pg, int i0, int p[], int lambda[]){

	int i, j;
	int s;
	int lambdamin;
	int listeS[NMAX];
	p[i0] = -1;
	lambda[i0] = 0;
	for(i=0; i<pg->n; i++){
		lambda[i] = LMAX;
		listeS[i]=0;
	}
	listeS[i0]=1;
	lambda[i0]=0;
	i = i0;
	while(somme(listeS,pg->n)!=pg->n){
		j= successeur(i , -1, pg);
		printf("Premier successeur de %d = %d\n", i, j);
		while(j != -1){
			if(listeS[j] == 0){
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
		lambdamin=1+pg->n*LMAX;
		i=-1;
		for(s=0; s<pg->n; s++){
			if(listeS[s] == 0 && lambda[s] < lambdamin){
				i=s;
				lambdamin=lambda[i];
			}
		}
		printf("On sélectionne le sommet %d de marque minimum lambda = %d\n", i, lambdamin);
		listeS[i]=1;	
	}
}




























