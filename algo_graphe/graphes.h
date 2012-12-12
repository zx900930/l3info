#define TRUE 1
#define FALSE 0
#define LMDMAX 100000
#define INFINITY  100000  /*infinity*/
#define MAX_VERTEX_NUM 20   	/*sommet_max*/

/* ================== types ====================*/



typedef int Boolean;



typedef struct Graphe {
    	int n;
	int tab[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
} graphe;




/*======================== prototypes =====================*/ 

int adj(int,int,graphe*);
void addArc(int,int,graphe*, int);
void addEdge(int,int,graphe*, int);
void affiche(graphe *);
//int degre(graphe *, int);
//int degreExt(graphe *, int);
//int degreInt(graphe *, int);
int successeur(graphe* pg, int i, int j);
void graphe_init(graphe* pg);
int somme(int [], int);
void dfsx0 (graphe *pg, int x0, int suffixe[]);
void explore(graphe *pg, int x, int marque[MAX_VERTEX_NUM], int suffixe[MAX_VERTEX_NUM], int k);
void Dijkstra(graphe* pg, int i0, int p[], int lambda[]);




