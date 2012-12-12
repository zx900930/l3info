#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

pthread_t thread[2];

int compteA = 30000;
int compteB = 0;

int transfert_money(){
	int somme;

	if(compteA<1000){
		somme = compteA;
	}
	else{
		somme = rand()%1000;
	}
	compteA -= somme;
	compteB += somme;

	printf("A --> B  %d\n",somme);
	printf("compte_a = %d\n",compteA);
	printf("compte_b = %d\n",compteB);

	return compteA;
}

void *transaction(void *arg){
	while(compteA != 0){
		transfert_money();
	}
}

int main(){
	int i;
	
	printf("\nINITIAL:\nCOMPTE A = %d & COMPTE B = %d\n",compteA,compteB);
	printf("\nETAPES:\n");

	for(i=0;i<2;i++){
		if((pthread_create(&thread[i],NULL,transaction,(void *)i))==-1){
			perror("Erreur thread");
			exit(-1);
		}
	}
	for(i=0;i<2;i++){
		pthread_join(thread[i],NULL);
	}

	printf("\nFINAL: COMPTE_A = %d & COMPTE_B = %d\n\n",compteA,compteB);	

	return EXIT_SUCCESS;	
}
