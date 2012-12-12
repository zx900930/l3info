%{
#include<stdlib.h>
#include "exo.tab.h"
int nbligne = 0;
%}

chiffre 	[0-9]
entier 		{chiffre}+
espace 		[ \t]

%%
somme 		return(SOMME);
produit 	return(PRODUIT);
\n 		nbligne++;
[.,] 		return(yytext[0]);
{entier} 	{yylval = atoi(yytext); return(NOMBRE);}
{espace}+ 	/* rien */;
"$" 		return(FIN);
.		printf("erreur à la ligne %d; %c inconnu\n",nbligne,yytext[0]);
%% 
