%{
int ligne, mot, nbCaractere;
%}
alpha		[a-zA-Z]
mot		{alpha}+
espace		[\t ]+
%%
{mot}		{mot++;
		nbCaractere += yyleng;
		}
{espace}	{nbCaractere += yyleng;}
\n		{ligne++;
		nbCaractere += yyleng;
		}
%%

main(){
	ligne = mot = nbCaractere = 0;
	yylex();
	printf("Il y a %d lignes, %d mots et %d caracteres\n", ligne, mot, nbCaractere);
}
