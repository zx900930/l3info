#include"grapheLA.h"
#include<stdlib.h>
#include<stdio.h>

int main(){
	grapheLa graphe;
	graphe.n=3;
	init(&graphe);
	addEdge(0,1,&graphe);
	addEdge(1,2,&graphe);
	addEdge(0,2,&graphe);	

	afficheGraphe(&graphe);
	//printf("Le degre de 2 est %d, son degré intérieur est %d, son degré extérieur est %d\n", degre(&graphe, 2), degreInterieur(&graphe, 2), degreExterieur(&graphe, 2));

	return EXIT_SUCCESS;
}
