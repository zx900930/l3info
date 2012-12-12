#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	Stack p=NULL;
	pushStack(&p, "Hello");
	pushStack(&p, "Hello1");
	pushStack(&p, "Hello2");
 	displayStack(p);
	emptyStack(&p);
return EXIT_SUCCESS;
}
