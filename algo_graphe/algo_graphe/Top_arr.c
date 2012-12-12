/*=========================================================

       5.6 ©ÝŸë±Æ§Ç
	  šÏ¥ÎŸF±µ¯x°}

	  topolody_sort()  ©ÝŸë±Æ§ÇšçŠ¡
	  choose_next()    §äšìSELECTED¬°0¥B€J€À
			   €ä«×¬°0ªº³»ÂI


	  M[V][V]	¹Ï§ÎªºŸF±µ¯x°}
	  INDEGREE[V]	ŠU³»ÂIªº€J€À€ä«×,ªì³]¬°0
	  SELECTED[V]	ŒÐŠWŠU³»ÂI¬O§_€w³Q¿é¥X,ªì³]¬°0

  =========================================================
*/

#include <stdio.h>

#define V	9

int M[V][V]={	{0,1,1,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0},
		{0,0,0,0,1,0,0,1,0},
		{0,0,0,0,0,1,1,1,0},
		{0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0,0,0}};

int INDEGREE[V];
char SELECTED[V];

void topolody_sort();
int choose_next();

void main(void)
{
    /*clrscr();*/
    topolody_sort();
}

void topolody_sort(void)
{
    int i,j;
    int Vx;
    for (i=0;i < V;i++)
		INDEGREE[i]=SELECTED[i]=0;
    for(i=0;i < V;i++)
		for(j=0;j < V;j++)
			if(M[i][j] == 1)
				INDEGREE[j]++;

    for(i=0;i < V;i++)
    {
		Vx=choose_next();
		printf("%d",Vx);
		for(j=0;j < V;j++)
			if (M[Vx][j] == 1)
			{
				M[Vx][j]=0;
				INDEGREE[j]--;
			}
	}	
}

int choose_next(void)
{
    int i;
    for(i=0;i < V;i++)
	if (!SELECTED[i] && !INDEGREE[i])
	{
		SELECTED[i]=1;
		return(i);
	}
}
