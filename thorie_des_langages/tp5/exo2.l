lettre		[a-zA-Z]
%%
\\cad						printf("c'est-à-dire");
\\cad{lettre}+|{lettre}+\\cad			printf("%s", yytext);
\\ssi						printf("si et seulement si");
\\ssi{lettre}+|{lettre}+\\ssi			printf("%s", yytext);
\\afd|\\AFD					printf("automate fini déterministe");
\\afd{lettre}+|{lettre}+\\afd			printf("%s", yytext);
\\thlang					printf("théorie des langages");
\\thlang{lettre}+|{lettre}+\\thlang		printf("%s", yytext);
%%
