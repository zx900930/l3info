#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#define N 3

int mat1[N][N], mat2[N][N], mat_res[N][N];
pthread_t t[N*N];

void rand_mat(int tab[N][N]){
	int i, j;
	for(i = 0; i<N ; i++){
		for(j = 0; j<N; j++){
			tab[i][j] = rand()%10;
		}
	}
}

void affiche(int tab[N][N]){
	int i, j;
	for(i = 0; i<N ; i++){
		printf("-");
		for(j = 0; j<N; j++){
			printf(" %d ", tab[i][j]);
		}
		printf("-\n");
	}
	printf("\n");
}

void * mult(void * indice){
	int i = (int) indice;
	int k;
	for(k = 0; k < N; k++){
		mat_res[i/N][i%N] = mat1[i/N][k] * mat2[k][i%N];
	}
}

int main(){

	int i;
	rand_mat(mat1);
	affiche(mat1);
	rand_mat(mat2);
	affiche(mat2);
	for(i = 0; i < N*N; i++){
		if ((pthread_create(&t[i], NULL, mult, (void *) i)) == -1){
			perror("Erreur thread");
			exit(-1);
		}
	}
	for(i = 0; i < N*N; i++){
		pthread_join(t[i], NULL);
	}
	affiche(mat_res);
	
	return EXIT_SUCCESS;
}
