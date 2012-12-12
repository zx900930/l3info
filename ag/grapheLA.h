#ifndef __GRAPHELA__
#define __GRAPHELA__

#define NMAX 100

typedef struct cellule{
	int noeud;
	struct cellule * psucc;
} cellule;


typedef struct grapheLa{
	cellule* tab[NMAX];
	int n;
} grapheLa;

void init(grapheLa *);
void addArc(int,int,grapheLa*);
void addEdge(int,int,grapheLa*);
//int adjacent(int,int,grapheLa*);
void afficheGraphe(grapheLa*);
/*int degre(grapheLa *, int);
int degreExterieur(grapheLa *, int);
int degreInterieur(grapheLa *, int);*/

#endif
