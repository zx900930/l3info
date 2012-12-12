#include <stdio.h>
#include <stdlib.h>

int fact (int x){
	if(x == 1 || x ==0) return 1;
		if(x < 0){ 
			perror("erreur");
			exit(-1);
		}
		else return x * fact(x-1);
	}
}

int factn(int n){
	int i;
	for(i = 0; i<n; i++){
		fact(5);
	}
}
