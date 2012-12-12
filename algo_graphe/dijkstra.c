#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define INFINI 255; 

typedef struct tsommet
{
    ushort x;              // le numero du sommet
    ushort d;              // distance par rapport au sommet prÃ©Ã©dent.  
    struct tsommet * suiv; // le pointeur vers la cellule suivante.
} TSOMMET;

typedef struct tsommet * tliste; // tliste = pointeur sur sommet
typedef tliste * tgraphe;        // tgraphe = tableau de liste de sommets

tgraphe G;    // declaration du graphe G (listes d'adjacence)
ushort *dmin; // tableau des distances minimales en partant de s
ushort *E;    // ensemble des sommets;
ushort *pere; // tableau des pÃ¨res;
ushort s;     // sommet de depart;
ushort n;     // ordre du graphe (nombre de sommets);
char *nomfic; // nom du fichier sur disque

void inserer(ushort x, short dxy, tliste *L)
    // insere un nouveau sommet + sa distance au précédent
    // dans la liste d'adjacence L
{
    if ((*L) == NULL)
    {
	(*L) = (tliste) malloc (sizeof(struct tsommet));
	(*L)->x = x;
	(*L)->d = dxy;
	(*L)->suiv = NULL;
    }
    else
	inserer(x, dxy, &((*L)->suiv));
}

void AfficDmin(ushort *dmin)
    // affiche les distances minimales et les chemins
    // correspondant partants de s
{
    ushort i = 0;
    ushort y;

    for (i = 0; i < n; i++)
    {
	printf("dmin(%d,%d) = %3d\t\t",s,i,dmin[i]);
	y = i;
	if ((dmin[y] != 255) && (dmin[y] != 0)) 
	{
	    printf("%d<",y);
	    while (pere[y] != s)
	    {
		printf("%d<",pere[y]);
		y = pere[y];
	    }
	    printf("%d",s);
	}
	printf("\n");
    }
}

void AfficGraphe(tgraphe G)
    // uniquement pour vérifier 
{
    int i = 0;
    tliste L;

    for (i = 0; i < n; i++)
    {
	printf("[%d]",i);
	L = G[i];
	while (L != NULL)
	{
	    printf(" -- %d --> [%d]", L->d, L->x);
	    L = L->suiv;
	}
	printf("\n");
    } 
}

void Init(int n,int s)
{
    int i = 0;

    dmin = (ushort *) malloc (n * sizeof(short)); 
    pere = (ushort *) malloc (n * sizeof(ushort));
    E = (ushort *) malloc (n * sizeof(ushort));
    for (i = 0; i < n; i++) 
    {    
	dmin[i] = INFINI;
	pere[i] = i;
	E[i] = 1;
    }
    dmin[s] = 0;
}

short ChercherMin(ushort *dmin)
{
    int i = 0;

    ushort min = INFINI;
    short x = -1;

    for (i = 0; i < n; i++)
	if ((E[i]) && ((dmin[i]) < min))
	{
	    x = i;
	    min = dmin[x];
	}
    return(x);
}

void relacher(ushort x, ushort y, ushort d)
{
    if (dmin[x] + d < dmin[y])
    {
	dmin[y] = dmin[x] + d;
	pere[y] = x;
    }
}

void Dijkstra(tgraphe G, int n, int s)
{
    short x;
    tliste L;

    Init(n,s); 
    while ((x = ChercherMin(dmin)) >= 0) // il reste des sommets dans E
    {
	L = G[x];
	while (L != NULL)
	{ 
	    relacher(x,L->x,L->d);	      
	    L = L->suiv;
	}
	E[x] = 0;            // elimine le sommet x de E.
    }
}

ushort ChargerGraphe(char * nomfic, tgraphe *G)
{
    FILE *source; // descripteur du fichier graphe
    int x,y,dxy,n;

    source = fopen(nomfic,"r");
    fscanf(source,"%d ",&n);
    (*G) = (tliste *) malloc (n * sizeof(tliste));  // allocation du graphe 
    while (fscanf(source,"%d %d %d", &x, &y, &dxy) != EOF)
	inserer(y,dxy,&((*G)[x])); // insertion d'un nouvel arc dans G
    fclose(source);
    return(n);
}

int main(int argc, char * argv[])
{
    if (argc < 3)
    {
	printf("syntaxe: %s fichier_graphe sommet_depart\n",argv[0]);
	return(1);
    }

    s = atoi(argv[2]);            // sommet de depart.
    n = ChargerGraphe(argv[1], &G);  // initialisation de l'ordre du graphe.
#ifdef IF_DEBUG
    AfficGraphe(G);               // affichage de vÃ©rification du graphe.
#endif
    Dijkstra(G,n,s);
    AfficDmin(dmin);
    free(dmin);
    free(E);
    free(pere);
    return(0);
}
