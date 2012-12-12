/*

Codage d'un automate travaillant sur l'alphabet a..z,
ayant au maximum MAX_ETAT états,
et lisant ces entrées dans stdin.

Pour le mode verbose :
 gcc automate.c -DTRACE -g -Wall -o automate      

ZHOU Xiong 2012 L3 INFO

 */

#include <stdio.h>

#define MAX_ETAT 20
#define ACCEPTATION 0
#define ECHEC       1


/* Tableau du status des etats (ACCEPTATION ou ECHEC) */
int status_etat[MAX_ETAT];

/* Tableau des transition MAX_ETAT x 26 */
int transition[MAX_ETAT][26];

/*----------------------------------------------------------------------*/
void construire_status_etat()
{
  int i;

  /* Par defaut, ils sont en status ECHEC */
  for(i=0;i<MAX_ETAT;i++) status_etat[i]=ECHEC;

  /* On ajoute à la main les etats ACCEPTATION */
  status_etat[3]= ACCEPTATION;
}
/*----------------------------------------------------------------------*/
void construire_transition()
{
  int i,j;		//i= noEtat et j=lettreTransition

  /* Par defaut, toutes les transitions sont interdites */
  for(i=0;i<MAX_ETAT;i++)
    for(j=0;j<26;j++)
      transition[i][j]=-1;

  /* On ajoute à la main les transitions */
  /* Note : a=0, b=1, ..., z=25 */
  /* l'automate reconnait l'expression (a.a.b.b*)* */

  /* transition 0 lettre a 1 */
  transition[0][0]=1;

  /* transition 1 lettre a 2 */
  transition[1][0]=2;

  /* transition 2 lettre b 3 */
  transition[2][1]=3;

  /* transition 3 lettre a 1 */
  transition[3][0]=1;

  /* transition 3 lettre b 3 */
  transition[3][1]=3;
}

void produit()
{
	int i,j;

	














}

/*----------------------------------------------------------------------*/
char lire(){
  return( (char)getchar());
}
/*----------------------------------------------------------------------*/
int code_lettre(char l)
{
  return((int)(l-'a'));
}
/*----------------------------------------------------------------------*/
int automate()
{
  char lu; /* caractere lu */
  int e=0; /* etat courant */

  printf("Entrer un mot suivit d'un point (.):\n");

  lu=lire();
 
 while(lu !='.'){
#ifdef TRACE 
  printf("état %d, lettre lue %c, prochaine état %d\n",e,lu,transition[e][code_lettre(lu)]);
#endif
   e=transition[e][code_lettre(lu)];
   if(e==-1) return(ECHEC);
   
   lu=lire();
  }

 return status_etat[e];
}

/*----------------------------------------------------------------------*/
/*                                MAIN                                  */
/*----------------------------------------------------------------------*/
int main()
{
//  char lu;

  construire_status_etat();
  construire_transition();

  if(automate()==ECHEC) printf("Non reconnu !\n"); else printf("Reconnu !\n");

return 0;
}
