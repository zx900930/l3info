#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"semaphore.h"

int a = 2, b = 5, c = 3, d = 4, e = 0, f = 0;

int main(){

	pid_t pid1, pid2;
	printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);
	init_semaphore();
	pid1 = fork();
	pid2 = fork();
	
	if(pid1 > 0){ //premier bloc
		if(pid2 > 0){ //T1 a+b
			printf("a + b = %d\n", a + b);
			V(0);
		}
		if(pid2 == 0){ //T3 (a+b)-(c+d)
			P(0);
			P(1);
			printf("(a+b)-(c+d) = %d\n", ((a+b)-(c+d)));
		}
	}
	if(pid1 == 0){ //deuxième bloc
		if(pid2 > 0){ //T2 c+d
			printf("c + d = %d\n", c + d);
			V(1);
			V(2);
		}
		if(pid2 == 0){ //T4 2*(c+d)
			P(2);
			printf("2 * (c + d) = %d\n", (2 * (c + d)));
		}
	}
	return EXIT_SUCCESS;
}


	
	
	
