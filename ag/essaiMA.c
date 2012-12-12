#include"grapheMA.h"
#include<stdlib.h>
#include<stdio.h>

int main(){

	grapheMa graphe;
	graphe.n=3;
	init_graphe(&graphe);
	int pere[graphe.n];
	int lambda[graphe.n];
	int i;

	addArc(0,1,&graphe,8);
	addArc(1,2,&graphe,9);
	addArc(2,0,&graphe,1);	

	afficheGraphe(&graphe);
	//warshall(&graphe, &graphet);
	Dijkstra(&graphe, 0, pere, lambda);
	printf("\n\n\n");
	for(i =0; i<3; i++){
		printf("père de %d:%d et lambda :%d\n",i,pere[i],lambda[i]);
	}
	
	//printf("Le degre de 2 est %d, son degré intérieur est %d, son degré extérieur est %d\n", degre(&graphe, 2), degreInterieur(&graphe, 2), degreExterieur(&graphe, 2));

	return EXIT_SUCCESS;
}
