#include <stdio.h>
#include <stdlib.h>

#define S	5

int M[S][S]={ {0,0,1,1,0,0},
	      {1,1,0,0,1,1},
	      {2,1,0,0,1,0},
	      {3,0,1,1,0,1},
	      {4,0,1,0,1,0},};

int Indegree[S];
char Selected[S];

void Topo_Sort(void);
int choose_next(void);

int main(int argc, char *argv[])
{
    Topo_Sort();
    return 0;
}

void Topo_Sort(void)
{
    int i,j;
    int Vx;
    for (i=0;i < S;i++)
		Indegree[i]=Selected[i]=0;
    for(i=0;i < S;i++)
		for(j=0;j < S;j++)
			if(M[i][j] == 1)
				Indegree[j]++;

    for(i=0;i < S;i++)
    {
		Vx=choose_next();
		printf(" S%d ",Vx);
		for(j=0;j < S;j++)
			if (M[Vx][j] == 1)
			{
				M[Vx][j]=0;
				Indegree[j]--;
			}
	}
	printf("\n");
}

int choose_next(void)
{
    int i;
    for(i=0; i < S; i++)
		if (!Selected[i] && !Indegree[i])
		{
			Selected[i]=1;
			return(i);
		}
	return (-1);
}
