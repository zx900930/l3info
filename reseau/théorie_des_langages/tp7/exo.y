%token SOMME
%token DIFFERENCE
%token PRODUIT
%token QUOTIENT
%token NEG
%token PARENTHESE
%token NOMBRE
%token FIN
%%

texte : FIN {printf("Au revoir\n");YYACCEPT;}
	;

E : SOMME sentiers {printf("la somme est %d\n",$2);};
	|DIFFERENCE dentiers {printf("la différence est de %d\n",$2);};
	|T NOMBRE {$$=yylval;};
	;

T : PRODUIT pentiers {printf("le produit est %d\n",$2);};
	|QUOTIENT qentiers {printf("le quotient est %d\n",$2);};
	|F NOMBRE {$$=yylval;};
	;

F : NEG NOMBRE {$$=-yylval;};
	|NOMBRE {$$=yylval;};
	;



sentiers : sentiers ',' NOMBRE {$$=$1+yylval;}
	|NOMBRE {$$=yylval;}
	;

pentiers : pentiers ',' NOMBRE {$$=$1*yylval;}
	|NOMBRE {$$=yylval;}
	;

dentiers : dentiers ',' NOMBRE {$$=$1-yylval;}
	|NOMBRE {$$=yylval;}
	;

qentiers : qentiers ',' NOMBRE {$$=$1/yylval;}
	|NOMBRE {$$=yylval;}
	;
%%
