#ifndef __grapheMa__
#define __grapheMa__

#define NMAX 100
#define LMAX 10000
#define N -100000

typedef struct grapheMa{
	int tab[NMAX][NMAX];
	int n;
} grapheMa;

void addArc(int,int,grapheMa*, int);
void addEdge(int,int,grapheMa*, int);
int adjacent(int,int,grapheMa*);
void affichegrapheMa(grapheMa*);
int degre(grapheMa *, int);
int degreExterieur(grapheMa *, int);
int degreInterieur(grapheMa *, int);
int successeur(grapheMa* pg, int a, int b);
void warshall (grapheMa*, grapheMa*);
void init_grapheMa(grapheMa* pg);
int somme(int [], int);

#endif
