#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int pushStack(Stack *s, char * elt){
	Stack m = malloc (sizeof(maillon));

	if (m == NULL){
	printf("MALLOC");
	return 1;
	}

	m -> item = elt;
	m -> next = (*s);
	*s = m;
	return 0;
}	


char* popStack(Stack *s){
	char *resultat;
	Stack tmp;
	if (*s ==NULL)
	return NULL;
	resultat = (*s) -> item;
	tmp = *s ;
	*s = tmp -> next;
	return resultat;	
}

void emptyStack(Stack *s){
	Stack tmp;
	while(*s != NULL){
		tmp = *s;
		*s = (*s) -> next;
		free (tmp);
	} 

}

int sizeofStack(Stack s){
	int resultat = 0;
	while (s != NULL){
	resultat += 1;
	s = s -> next;
	} return resultat;
}


void displayStack(Stack s){
	while(s != NULL){
	printf("item = %s\n", s -> item);
	s = s -> next;
	}
	printf("fond de pile");
}
