#include"washall.h"
#include<stdlib.h>
#include<stdio.h>

int main(){

	grapheMa graphe;
	graphe.n=3;
	init_graphe(&graphe);
	int i;

	addArc(0,1,&graphe,8);
	addArc(1,2,&graphe,2);
	addArc(0,2,&graphe,7);	

	//afficheGraphe(&graphet);
	//warshall(&graphe, &graphet);
	
	printf("Le degre de 2 est %d, son degré intérieur est %d, son degré extérieur est %d\n", degre(&graphe, 2), degreInterieur(&graphe, 2), degreExterieur(&graphe, 2));

	return EXIT_SUCCESS;
}
