%%

mot : IaPb '@' {printf("Mot accepté\n"); YYACCEPT;}
	;

PaPb : 'a' IaPb
     | 'b' PaIb
     |
     ;

PaIb : 'a' IaIb
     | 'b' PaPb
     | 'b'
     ;

IaPb : 'a' PaPb
     | 'b' IaIb
     | 'a' 
     ;

IaIb : 'a' PaIb
     | 'b' IaPb
     | 'a' 'b'
     | 'b' 'a'
     ;

%%

int yylex(){
	char car = getchar();
	if(car == 'a' || car == 'b' || car == '@') return (car);
	else printf ("Erreur, le caractère %c est non reconnu\n", car);
}
