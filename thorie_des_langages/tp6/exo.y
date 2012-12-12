%token SOMME
%token PRODUIT
%token NOMBRE
%token FIN
%%


texte : liste texte
	|FIN {printf("A+\n");YYACCEPT;}
	;

liste : SOMME sentiers {printf("la somme est %d\n",$2);}
	|PRODUIT pentiers {printf("le produit est %d\n",$2);}
	;

sentiers : sentiers ',' NOMBRE {$$=$1+yylval;}
	|NOMBRE {$$=yylval;}
	;

pentiers : pentiers ',' NOMBRE {$$=$1*yylval;}
	|NOMBRE {$$=yylval;}
	;
%%
