%{
%}


%%
^p[a-z]*\n
^P[a-z]*\n
o		printf("*");
%%

main(){
	yylex();
}
