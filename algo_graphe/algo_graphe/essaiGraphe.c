# include "graphes.h"	


int main(){
	graphe g;
	int suffixe[MAX_VERTEX_NUM];
	int i,j;
	/* initialisation*/
	g.n=4;
	for (i=0; i<g.n;i++)
		for (j=0; j<g.n;j++)
			g.tab[i][j]= -INFINITY;
	g.tab[0][1]= 10;
	g.tab[1][2]= 10;
	g.tab[0][2]= 10;
	g.tab[0][3]= 10;
	/* */
	dfsx0(&g,0, suffixe);
	return 0;
}
	
