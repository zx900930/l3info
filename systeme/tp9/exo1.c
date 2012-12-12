#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int x, y;
pthread_mutex_t mut;
pthread_cond_t cond;


void *alarme(void * arg){
    while(1){
	pthread_mutex_lock(&mut);
	pthread_cond_wait(&cond,&mut);
	printf("ALERTE ! x = %d, y = %d\n",x,y);
	pthread_mutex_unlock(&mut);
    }
}

void *senseur1(void * arg){
    while(1){
	pthread_mutex_lock(&mut);
	x = rand() % 20;
	y = rand() % 20;
	if(x>y){
	    pthread_cond_signal(&cond);
	}	
	pthread_mutex_unlock(&mut);
    }
}

int main(int argc, char * argv[]){
    pthread_t t1,t2;
    /*initialisation*/
    if(pthread_cond_init(&cond,NULL))
    {
	perror("cond_init error");
	exit(1);
    }


    if(pthread_mutex_init(&mut,NULL))
    {
	perror("mutex_init error");
	exit(2);
    }

    /*création des threads*/
    if(pthread_create(&t1,NULL,alarme,NULL)){
	printf("create thread 1 failed");	
    }

    if(pthread_create(&t2,NULL,senseur1,NULL)){
	printf("create thread 2 failed");	
    }

    /*join*/
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
