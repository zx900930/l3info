#include "automate.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
	automate_t *b;
	char d[2]={'a','b'};
	b=creer_automate(5,2,d);
	init_transition(b,1,4,0);
	init_transition(b,4,3,1);
	init_transition(b,2,3,0);
	init_transition(b,4,3,0);
	
	affiche_auto(b);
	
return EXIT_SUCCESS;
}
