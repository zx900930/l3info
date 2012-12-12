#ifndef __GRAPHEMA__
#define __GRAPHEMA__

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
void afficheGraphe(grapheMa*);
int degre(grapheMa *, int);
int degreExterieur(grapheMa *, int);
int degreInterieur(grapheMa *, int);
int successeur(grapheMa* pg, int a, int b);
//void parcoursP(grapheMa*);
void warshall (grapheMa*, grapheMa*);
void init_graphe(grapheMa* pg);
int somme(int [], int);
void Dijkstra(grapheMa*, int, int*, int*);

#endif
