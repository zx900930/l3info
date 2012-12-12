#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "semaphore.h"

static int semid=-1; /* identification de l'ensemble des semaphores */

union semun {
             int             val;
             struct semid_ds *buf;
             unsigned short        *array;
     };

/*** creation et initialisation des semaphores : la fonction renvoie 0
     en cas de reussite, -2 en cas d'echec et -1 si ensemble deja cree ***/

int init_semaphore(void){
  int i;
  union semun arg;
  if(semid!=-1){
    fprintf(stderr,"Creation deja realisee.\n");
    return -1;
  }
  if((semid=semget(IPC_PRIVATE,NBRE_SEM,IPC_CREAT|0666))==-1){
    fprintf(stderr,"Creation des semaphores impossible.\n");
    return -2;
  }
  /* initialisation des semaphores a 0 */
  arg.val = 0;
  for(i=0;i<NBRE_SEM;i++) semctl(semid,i,SETVAL,arg);
  return 0;
}

/*** suppression de l'ensemble des semaphores ***/
int detruire_semaphore(void){
  int val;
  if(semid==-1){
    fprintf(stderr,"Semaphores non crees.\n");
    return -1;
  }
  val=semctl(semid,0,IPC_RMID,NULL);
  semid=-1;
  return val;
}

/*** initialisation du semaphore de numero donne a la valeur donne ***/
int val_sem(int numero,int val){
  if(semid==-1){
    fprintf(stderr,"Semaphores non crees.\n");
    return -1;
  }
  if((numero<0) || (numero>= NBRE_SEM)){
    fprintf(stderr,"Numero de semaphore incorrect.\n");
    return -2;
  }
  return(semctl(semid,numero,SETVAL,val));
}

/*** P et V ***/
static struct sembuf op_P={-1,-1,0},/* operation P:2ieme champ = -1 */
  op_V={-1,1,0};

int P(int numero){
  if(semid==-1){
    fprintf(stderr,"Semaphores non crees.\n");
    return -1;
  }
  if((numero<0)||(numero>=NBRE_SEM)){
    fprintf(stderr,"Numero de semaphore incorrect.\n");
    return -2;
  }
  op_P.sem_num=numero;
  return(semop(semid,&op_P,1));
}

int V(int numero){
  if(semid==-1){
    fprintf(stderr,"Semaphores non crees.\n");
    return -1;
  }
  if((numero<0)||(numero>=NBRE_SEM)){
    fprintf(stderr,"Numero de semaphore incorrect.\n");
    return -2;
  }
  op_V.sem_num=numero;
  return(semop(semid,&op_V,1));
}
