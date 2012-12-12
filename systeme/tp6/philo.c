#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>
#include<semaphore.h>

#define N_PHILO 50
#define N_BAGUETTES 50

pthread_mutex_t baguettes[50];
sem_t table;
pthread_t tab[50], nettoyeur;
int arret = 0;

void penser(int i){
	printf("Le philosophe %d est en train de penser.\n", i);
	sleep((rand()%10));
}

void manger(int i){
	printf("Le philosophe %d est en train de manger.\n", i);
	sleep(rand()%10);
}

void * philosophe(void *p){

	int i = (int) p;
	sigset_t masque;
	sigemptyset(&masque);
	sigaddset(&masque, SIGINT);
	pthread_sigmask(SIG_BLOCK, &masque, NULL);
	while(!arret){
		penser(i);
		sem_wait(&table);
		pthread_mutex_lock(&baguettes[i]);
		pthread_mutex_lock(&baguettes[(i+1)%50]);
		manger(i);
		pthread_mutex_unlock(&baguettes[i]);
		pthread_mutex_unlock(&baguettes[(i+1)%50]);
		sem_post(&table);
	}		
	return(0);
}

void liberation(){
	int i;
	for(i = 0; i < 50; i++){
		pthread_mutex_destroy(&baguettes[i]);
	}
	sem_destroy(&table);
}

void * terminator(void * arg){
	int numero, i;
	sigset_t masque;
	sigemptyset(&masque);
	sigaddset(&masque, SIGINT);
	sigwait(&masque, &numero);
	arret = 1;
	printf("Déclenchement de terminator, veuillez patienter\n");
	for(i = 0; i < 50; i++){
		pthread_join(tab[i], NULL);
	}
	liberation();
	exit(1);
		
}

int main(){

	int i;
	sigset_t masque;
	sem_init(&table, 0, 49);
	sigemptyset(&masque);
	sigaddset(&masque, SIGINT);
	pthread_sigmask(SIG_BLOCK, &masque, NULL);
	for(i = 0; i < 50; i++){
		pthread_mutex_init(&baguettes[i], NULL);
	}
	for(i = 0; i < 50; i++){
		pthread_create(&tab[i], NULL, philosophe, (void*) i);
	}	
	pthread_create(&nettoyeur, NULL, terminator, NULL);
	pthread_join(nettoyeur, NULL);
	return EXIT_SUCCESS;
} 
