%{
%}

lettre		[a-zA-Z]
espace		[ \t]*
vide		\n*

%%
{espace}			printf(" ");
{vide}				printf("\n");
{espace}$
%%
