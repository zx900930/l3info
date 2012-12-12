%{
%}

lettre		[a-zA-Z]
espace		[ ]*
vide		\n*

%%
bon				printf("mauvais");
bon{lettre}|{lettre}bon		printf("%s", yytext);
{espace}			printf(" ");
{vide}				printf("\n");
%%

main(){
	yylex();
}
