#include <stdio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2
#define OK 1
#define ERROR 0
typedef int Status;

#define INFINITY INT_MAX    /*infinity*/
#define MAX_VERTEX_NUM 20   /*sommet_max*/
typedef int Boolean;
typedef char VertexType[20];
typedef int  VRType;



/****define queue****/
typedef int QElemType;
typedef struct QNode
   {QElemType data;
    struct QNode *next;
   } QNode, *QueuePtr;

typedef struct
   {
    QueuePtr front;
    QueuePtr rear;
   } LinkQueue;

/****initialiser****/
Status InitQueue(LinkQueue *Q)
{ (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
  if (!(*Q).front) exit(OVERFLOW);
  (*Q).front->next=NULL;
  return OK; }

/****vide/no vide****/
Status QueueEmpty (LinkQueue Q)
{ if (Q.front==Q.rear)
     return TRUE;
  else
     return FALSE; }

/****entre queue****/
Status EnQueue(LinkQueue *Q, QElemType e)
{ QueuePtr p;
  p=(QueuePtr)malloc(sizeof(QNode));
  if (!p) exit(OVERFLOW);
  p->data=e; p->next=NULL;
  (*Q).rear->next=p;
  (*Q).rear=p;
  return OK; }

/****sortie queue****/
Status DeQueue(LinkQueue *Q, QElemType *e)
{ QueuePtr p;
  if ((*Q).front==(*Q).rear) return ERROR;
  p=(*Q).front->next;
  *e=p->data;
  (*Q).front->next=p->next;
  if ((*Q).rear==p) (*Q).rear=(*Q).front;
  free(p);
  return OK; }

/**************graphe************/


/*define*/
typedef struct ArcCell
    { VRType adj;     
      /* InfoType *info*/
    } ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct
    { VertexType vexs[MAX_VERTEX_NUM];  /*sommet*/
      AdjMatrix  arcs;                  /*matrice*/
      int vexnum,arcnum;                
    } MGraph;

/*matrice*/
void CreateGraph(MGraph *G)
{ int i,j,k; VertexType v1,v2;
  printf("\nInput MG vexnum,arcnum:");
  scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);

  printf("Input %d vexs:",(*G).vexnum);
  for(i=0;i<(*G).vexnum;i++)     /*entre sommet*/
    { scanf("%s",(*G).vexs[i]); }
  printf("vexs list\n");
  for(i=0;i<G->vexnum;i++)     /*sortie sommet*/
      puts(G->vexs[i]);

  for(i=0;i<(*G).vexnum;i++)     /*initialiser*/
     for(j=0;j<(*G).vexnum;j++)
	(*G).arcs[i][j].adj=0;

  printf("\nInput %d arcs(vi vj):\n",(*G).arcnum);
  for(k=0;k<(*G).arcnum;k++)     /*arretes*/
    { scanf("%s%s",v1,v2);
      i=LocateVex(*G,v1);  j=LocateVex(*G,v2);
      (*G).arcs[i][j].adj=1;
      (*G).arcs[j][i]=(*G).arcs[i][j];
    }
}

int LocateVex(MGraph G,VertexType v)
{ int i;
  for(i=0;i<G.vexnum;i++)
     if (strcmp(v,G.vexs[i])==0) break;
  return i;
}

int FirstAdjVex(MGraph G,int v)
{ int j,p=-1;
  for(j=0;j<G.vexnum;j++)
     if (G.arcs[v][j].adj==1) {p=j; break;}
  return p;
}

int NextAdjVex(MGraph G,int v,int w)
{ int j,p=-1;
  for(j=w+1;j<G.vexnum;j++)
     if (G.arcs[v][j].adj==1) {p=j; break;}
  return p;
}

/*output matrice*/
void PrintGraph(MGraph G)
{ int i,j;
  printf("\nMGraph:\n");
  for(i=0; i<G.vexnum; i++)
   { printf("%10s",G.vexs[i]);
     for(j=0; j<G.vexnum; j++)
        printf("%4d",G.arcs[i][j].adj);
     printf("\n");
   }
}

/*DFS*/

Boolean visited[MAX_VERTEX_NUM];  

void Dfs(MGraph G, int v)
{ int w;
  visited[v]=TRUE;
  printf("%s",G.vexs[v]);
  for(w=FirstAdjVex(G,v); w>=0; w=NextAdjVex(G,v,w))
     if(!visited[w]) Dfs(G,w);
}

void DfsTraverse(MGraph G)
{ int v;
  for (v=0; v<G.vexnum; v++)
      visited[v]=FALSE;
  for(v=0; v<G.vexnum; v++)
     if (!visited[v]) Dfs(G,v);
}



/*main*/
main()
{ int w;
  MGraph G;
  CreateGraph(&G);
  PrintGraph(G);
  printf("\nDfs:\n"); DfsTraverse(G);  /* DFS */
  }
