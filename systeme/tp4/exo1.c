#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

pthread_t th[2];
int a = 30000, b = 0, flag[2], turn;

void prologue(int self){
	flag[self] = 1;
	turn =! self;
	while(flag[!self] && turn == !self);
}

void epilogue(int self){
	flag[self] = 0;
}

void transfer_money(){
	int somme = 0;

	if (a < 1000){
		somme = a;
	}
	else{
		somme = rand()%1000;
	}
	a -= somme;
	b += somme;
	printf("Compte a = %d; Compte b = %d\n", a, b);
}	

void *transaction(void * arg){
	prologue((int) arg);
	while(a != 0){
		transfer_money();
	}
	epilogue((int) arg);
	printf("Valeur finale Compte a = %d; Compte b = %d\n", a, b);
}

int main(){
	int i;

	for(i = 0; i < 2; i++){
		pthread_create(&th[i], NULL, transaction, (void *) i);
	}

	for(i = 0; i < 2; i++){
		pthread_join(th[i], NULL);
	}
	return EXIT_SUCCESS;
}
